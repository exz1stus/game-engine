#include "engpch.h"
#include "Window.h"
#include "OpenGLCallbacks.h"

namespace eng
{
	Window::Window(const uint32_t width, const uint32_t height)
		:
		_width(width), _height(height),
		_glWindow(glfwCreateWindow(_width, _height, "game engine", NULL, NULL))
	{}

	Window::~Window()
	{
		glfwDestroyWindow(_glWindow);
	}

	void Window::MakeCurrentContext()
	{
		if (!_glWindow)
		{
			//assert
			std::cout << "glWindow is nullptr" << std::endl;
			return;
		}

		glfwMakeContextCurrent(_glWindow);
	}
	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(_glWindow);
	}
	void Window::BindWindowCallbacks() const
	{
		glfwSetWindowSizeCallback(_glWindow, WindowResizedCallback);
		glfwSetCursorPosCallback(_glWindow, MouseMovedCallback);
	}
	void Window::CenterCursor() const
	{
		glfwSetInputMode(_glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	bool Window::GetKey(uint16_t key) const
	{
		return glfwGetKey(_glWindow, key) == GLFW_PRESS;
	}
}