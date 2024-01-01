#include "engpch.h"
#include "Window.h"

namespace eng
{
	Window::Window(const uint32_t width, const uint32_t height)
		:
		_width(width), _height(height),
		_glWindow(glfwCreateWindow(_width, _height, "game engine", NULL, NULL))
	{
	}

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
	void Window::SwapBuffers()
	{
		glfwSwapBuffers(_glWindow);
	}
}