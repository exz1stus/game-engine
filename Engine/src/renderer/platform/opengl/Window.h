#pragma once
#include <glad.h>
#include "GLFW/glfw3.h"
namespace eng
{
	class Window
	{
	public:
		Window(const uint32_t width, const uint32_t height);
		~Window();

		void MakeCurrentContext();
		void SwapBuffers();
		bool GetKey(uint16_t key);
		bool IsClosed() { return glfwWindowShouldClose(_glWindow); }

		uint32_t GetWidth() const { return _width; }
		uint32_t GetHeight() const { return _height; }

	private:

		uint32_t _width;
		uint32_t _height;

		GLFWwindow* _glWindow;
	};
}
