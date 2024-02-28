#include "engpch.h"
#include "Renderer2D.h"
#include "RenderingEvents.h"
#include "RenderConfig.h"

#include "../AssetManager.h"
#include "platform/opengl/RenderingAPI.h"
#include "platform/opengl/Shader.h"
#include "platform/opengl/Texture2D.h"

#include "misc/Utilities.h"


namespace eng
{
	std::unique_ptr<Camera> Renderer2D::_cam;

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	struct RendererData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		//const uint32_t MaxTextureSlots = 32;			

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVerticesPtr;
		QuadVertex* QuadVerticesPtrBase; //starting point to not lose track of when incrementing ptr

		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<VertexBuffer> vbo;
		std::shared_ptr<IndexBuffer> ibo;

		std::shared_ptr<Shader> shader;

		glm::vec4 quadVerticesPositions[4];

		std::array<uint32_t, 32> TexSlots;
		uint32_t TextureSlotIndex = 1;
	};
	struct RenderingStatisticts
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCount = 0;
	};

	static RendererData renderData;
	static RenderingStatisticts renderStats;

	void Renderer2D::Init()
	{
		_cam = std::make_unique<Camera>(-350, 350, -300, 300, true);

		renderData.quadVerticesPositions[0] = { -0.5f, -0.5f, 0.0f , 1.0f, };//,	{0.0f, 0.0f} };
		renderData.quadVerticesPositions[1] = { 0.5f, -0.5f	, 0.0f , 1.0f, };//, { 1.0f, 0.0f } };
		renderData.quadVerticesPositions[2] = { 0.5f,  0.5f	, 0.0f , 1.0f, };//, { 1.0f, 1.0f } };
		renderData.quadVerticesPositions[3] = { -0.5f,  0.5f, 0.0f , 1.0f  };//, { 0.0f, 1.0f } };

		renderData.vbo = std::make_shared<VertexBuffer>(renderData.MaxVertices * sizeof(QuadVertex));
		renderData.vao = std::make_shared<VertexArray>();

		renderData.vbo->SetLayout({
		{ ShaderDataType::Float3, "a_Position"},
		{ ShaderDataType::Float4, "a_Color"}
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

		renderData.shader = AssetManager::GetAsset<Shader>("flatColor");
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (renderData.QuadIndexCount >= renderData.MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)renderData.TextureSlotIndex;
			//renderData.TexSlots[textureIndex] = texture.GetID();
		}

		static float rotation = 45.0f;

		glm::mat4 transform = glm::translate(
			glm::mat4(1.0f), glm::vec3(position, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < 4; i++)
		{
			renderData.QuadVerticesPtr->Position = transform * renderData.quadVerticesPositions[i];
			renderData.QuadVerticesPtr->Color = color;
			renderData.QuadVerticesPtr++;
		}
		renderData.QuadIndexCount += 6;
		renderStats.QuadCount++;
	}

	/*void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Texture2D& texture)
	{

	}*/

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
		renderData.shader->SetMat4("u_MVP", _cam->GetViewProjectionMatrix());

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
