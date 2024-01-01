#include "engpch.h"
#include "RenderingAPI.h"
namespace eng
{
	std::unique_ptr<Window> RenderingAPI::_window;

	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::cout << message << std::endl;
	}

	void RenderingAPI::Init()
	{

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		_window = std::make_unique<Window>(700, 600);

		_window->MakeCurrentContext();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//assert
			std::cout << "glad init failed" << std::endl;
		}
		
		SetViewport(0, 0, 700, 600);

		//debug messages
		glEnable(GL_DEBUG_OUTPUT);
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		glEnable(GL_DEPTH_TEST);

		//pixel blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderingAPI::SetViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
	{
		glViewport(x, y, width, height);
	}

	void RenderingAPI::DrawIndexed(const VertexArray& vao)
	{
		vao.GetIndexBuffer()->Bind();
		glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void RenderingAPI::PollEvents()
	{
		glfwPollEvents();
	}
	void RenderingAPI::SwapBuffers()
	{
		_window->SwapBuffers();
	}
}
