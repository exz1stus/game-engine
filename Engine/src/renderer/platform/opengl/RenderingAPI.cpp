#include "engpch.h"
#include "RenderingAPI.h"
#include "renderer/RenderingEvents.h"
#include "renderer/RenderConfig.h"
#include "GameTime.h"

namespace eng
{
	std::unique_ptr<Window> RenderingAPI::_window;

	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			Logger::Log(message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			//Logger::Warning(message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_HIGH:
			Logger::Error(message);
			break;
		default:
			Logger::Error(message);
			break;
		}

	}

	void RenderingAPI::Init()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		auto cfg = GetRenderConfig();

		_window = std::make_unique<Window>(cfg.WindowWidth, cfg.WindowHeight);

		_window->MakeCurrentContext();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//assert
			Logger::Error("glad init failed");
		}

		SetViewport(cfg.WindowWidth, cfg.WindowHeight);

		//debug messages
		glEnable(GL_DEBUG_OUTPUT);

		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		glEnable(GL_DEPTH_TEST);

		//pixel blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SetVSync(cfg.Vsync);

		RenderingEvents::OnWindowResized += SetViewport;
	}
	void RenderingAPI::SetViewport(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

	void RenderingAPI::DrawIndexed(const VertexArray& vao, const uint32_t indexCount)
	{
		vao.GetIndexBuffer()->Bind();
		uint32_t count = indexCount ? indexCount : vao.GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	void RenderingAPI::PollEvents()
	{
		if (_window->IsClosed()) RenderingEvents::OnWindowClosed();
		glfwPollEvents();
	}
	void RenderingAPI::SwapBuffers()
	{
		_window->SwapBuffers();
		//WaitForNextFrame();
	}
	void RenderingAPI::WaitForNextFrame()
	{
		double deltaTime = GameTime::GetDeltaTime();

		double targetFrameTime = 1.0 / 60.0; // 60 FPS
		if (deltaTime < targetFrameTime)
		{
			double sleepTime = targetFrameTime - deltaTime;
			GameTime::Sleep(sleepTime);
		}
	}
	void RenderingAPI::SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
	}
}
