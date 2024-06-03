#include "engpch.h"
#include "Renderer2D.h"
#include "RenderingEvents.h"
#include "RenderConfig.h"

#include "assets/AssetManager.h"
#include "platform/opengl/RenderingAPI.h"
#include "platform/opengl/Shader.h"
#include "platform/opengl/Texture2D.h"

#include "misc/Utilities.h"
#include "GameTime.h"
#include "misc/ApplicationVariables.h"

#include "ecs/SceneManager.h"

namespace eng
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct RendererData
	{
		const uint32_t MaxQuads = 20000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVerticesPtr;
		QuadVertex* QuadVerticesPtrBase; //starting point to not lose track of when incrementing ptr

		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<VertexBuffer> vbo;
		std::shared_ptr<IndexBuffer> ibo;
		std::shared_ptr<Shader> shader;
		glm::vec4 quadVerticesPositions[4];
		glm::vec2 texCoords[4];

		std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
		std::array<int, MaxTextureSlots> TextureSlotsIndices;
		uint32_t TextureSlotsUsed = 0;
	};
	struct RenderingStats
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCount = 0;
	};
	static RendererData renderData;
	static RenderingStats renderStats;
	const RenderingStats& GetStats()
	{
		return renderStats;
	}

	void Renderer2D::Init()
	{
		renderData.quadVerticesPositions[0] = { -0.5f, -0.5f, 0.0f , 1.0f, };
		renderData.quadVerticesPositions[1] = { 0.5f, -0.5f	, 0.0f , 1.0f, };
		renderData.quadVerticesPositions[2] = { 0.5f,  0.5f	, 0.0f , 1.0f, };
		renderData.quadVerticesPositions[3] = { -0.5f,  0.5f, 0.0f , 1.0f };

		renderData.texCoords[0] = { 0.0f, 0.0f };
		renderData.texCoords[1] = { 1.0f, 0.0f };
		renderData.texCoords[2] = { 1.0f, 1.0f };
		renderData.texCoords[3] = { 0.0f, 1.0f };


		renderData.vbo = std::make_shared<VertexBuffer>(renderData.MaxVertices * sizeof(QuadVertex));
		renderData.vao = std::make_shared<VertexArray>();

		renderData.vbo->SetLayout({
			{ ShaderDataType::Float3, "a_Position"     },
			{ ShaderDataType::Float4, "a_Color"        },
			{ ShaderDataType::Float2, "a_TexCoord"     },
			{ ShaderDataType::Float,  "a_TexIndex"     },
			{ ShaderDataType::Float,  "a_TilingFactor" }
			});

		uint32_t* quadIndices = new uint32_t[renderData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < renderData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		renderData.ibo = std::make_shared<IndexBuffer>(quadIndices, renderData.MaxIndices);
		delete[] quadIndices;

		renderData.QuadVerticesPtrBase = new QuadVertex[renderData.MaxVertices];

		renderData.vao->SetVertexBuffer(renderData.vbo);
		renderData.vao->SetIndexBuffer(renderData.ibo);

		renderData.shader = AssetManager::GetAsset<Shader>("textures");

		for (size_t i = 0; i < renderData.MaxTextureSlots; i++)
			renderData.TextureSlotsIndices[i] = i;

		renderData.shader->Bind();
		renderData.shader->SetArrInt("u_Textures",
			&renderData.TextureSlotsIndices[0], 32);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{

		DrawQuad(glm::vec3(position, 0.0f), glm::vec3(size, 0.0f), color, renderData.TextureSlots[0]);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture)
	{
		DrawQuad(glm::vec3(position, 0.0f), glm::vec3(size, 1.0f), color, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture)
	{
		float rotZ = 0.0f;
		glm::mat4 transform = glm::translate(
			glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f)); //use quat
		DrawQuad(transform, color, texture);
	}
	void Renderer2D::DrawQuad(const glm::mat4 transform, const glm::vec4& color, const std::shared_ptr<Texture2D> texture)
	{
		if (renderData.QuadIndexCount >= renderData.MaxIndices)
			NextBatch();

		float textureIndex = -1.0f;

		for (size_t i = 0; i < renderData.TextureSlotsUsed; i++)
		{
			if (*renderData.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			if (renderData.TextureSlotsUsed >= renderData.MaxTextureSlots)
				NextBatch();

			textureIndex = (float)renderData.TextureSlotsUsed;
			renderData.TextureSlots[renderData.TextureSlotsUsed] = texture;
			renderData.TextureSlotsUsed++;
		}

		for (size_t i = 0; i < 4; i++)
		{
			renderData.QuadVerticesPtr->Position = transform * renderData.quadVerticesPositions[i];
			renderData.QuadVerticesPtr->Color = color;
			renderData.QuadVerticesPtr->TexCoord = renderData.texCoords[i];
			renderData.QuadVerticesPtr->TexIndex = textureIndex;
			renderData.QuadVerticesPtr->TilingFactor = 1.0f;
			renderData.QuadVerticesPtr++;
		}
		renderData.QuadIndexCount += 6;
		renderStats.QuadCount++;
	}

	void Renderer2D::BeginScene()
	{
		StartBatch();
		renderStats.DrawCalls = 0;
		renderStats.QuadCount = 0;
	}

	void Renderer2D::StartBatch()
	{
		renderData.QuadIndexCount = 0;
		renderData.QuadVerticesPtr = renderData.QuadVerticesPtrBase;

		renderData.TextureSlotsUsed = 0;
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::Flush()
	{
		if (!renderData.QuadIndexCount) return;
		uint32_t dataSize = sizeof(QuadVertex) * renderData.QuadIndexCount * 4 / 6;
		renderData.vbo->SetData(renderData.QuadVerticesPtrBase, dataSize);

		renderData.shader->Bind();
		renderData.shader->SetMat4("u_MVP", SceneManager::GetMainCamera()->GetViewProjectionMatrix());

		for (size_t i = 0; i < renderData.TextureSlotsUsed; i++)
		{
			renderData.TextureSlots[i]->Bind(i);
		}

		renderData.shader->SetArrInt("u_Textures",
			&renderData.TextureSlotsIndices[0], renderData.TextureSlotsUsed);

		RenderingAPI::DrawIndexed(*renderData.vao, renderData.QuadIndexCount);
		renderStats.DrawCalls++;
	}
	void Renderer2D::EndScene()
	{	
		Flush();
		RenderingEvents::OnDrawUI();
		RenderingAPI::SwapBuffers();
		RenderingAPI::PollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}
