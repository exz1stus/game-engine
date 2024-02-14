#include "engpch.h"
#include "Renderer2D.h"
#include "RenderingEvents.h"
#include "RenderConfig.h"

#include "platform/opengl/RenderingAPI.h"
#include "platform/opengl/Shader.h"

#include "misc/Utilities.h"

namespace eng
{
	std::unique_ptr<Camera> Renderer2D::_cam;

	struct QuadVertex
	{
		glm::vec3 Position= {0,0,0};
	};

	struct RendererData
	{
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<VertexBuffer> vbo;
		std::shared_ptr<IndexBuffer> ibo;

		std::shared_ptr<Shader> shader;

		QuadVertex quadVertecies[4];
	};
	struct RenderingStatisticts
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCount = 0;
	};

	static uint32_t indicies[] = {
		0,1,2,
		2,3,0
	};

	static RendererData renderData;
	static RenderingStatisticts renderStats;

	void Renderer2D::Init()
	{
		RenderingAPI::Init();

		_cam = std::make_unique<Camera>(-350, 350, -300, 300, true);
		//_cam = std::make_unique<Camera>(0, 700, 0, 600, false);

		renderData.quadVertecies[0] = { {	-0.5f, -0.5f, 0.0f	} };//,	{0.0f, 0.0f} };
		renderData.quadVertecies[1] = { {	0.5f, -0.5f	, 0.0f	} };//, { 1.0f, 0.0f } };
		renderData.quadVertecies[2] = { {	0.5f,  0.5f	, 0.0f	} };//, { 1.0f, 1.0f } };
		renderData.quadVertecies[3] = { {	-0.5f,  0.5f, 0.0f	} };//, { 0.0f, 1.0f } };

		renderData.vbo = std::make_shared<VertexBuffer>((float*)renderData.quadVertecies, sizeof(renderData.quadVertecies));
		renderData.ibo = std::make_shared<IndexBuffer>(indicies, 6);
		renderData.vao = std::make_shared<VertexArray>();


		renderData.vbo->SetLayout({
		{ ShaderDataType::Float3, "a_Position"}
		});

		renderData.vao->SetVertexBuffer(renderData.vbo);
		renderData.vao->SetIndexBuffer(renderData.ibo);

		renderData.shader = Shader::LoadShader("flatColor");
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		float rotation = 0.0f;

		/*_cam->SetRotation(glm::vec3(0, 0, 0));
		_cam->SetPosition(glm::vec3(100, 0, 0));*/
		
		glm::mat4 transform = glm::translate(
			glm::mat4(1.0f), glm::vec3(position, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		renderData.shader->Bind();

		renderData.shader->SetMat4("u_MVP", _cam->GetViewProjectionMatrix() * transform);
		renderData.shader->SetFloat4("u_Color", color);

		RenderingAPI::DrawIndexed(*renderData.vao);

		renderStats.QuadCount++;
	}
	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
	}
	void Renderer2D::EndScene()
	{
		Flush();
	}
	void Renderer2D::Flush()
	{
		RenderingEvents::OnDrawUI();

		RenderingAPI::SwapBuffers();
		RenderingAPI::PollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	//batching
	void Renderer2D::StartBatch()
	{
	}
	void Renderer2D::NextBatch()
	{
	}
}
