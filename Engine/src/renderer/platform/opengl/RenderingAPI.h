#pragma once
#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace eng
{
	class RenderingAPI
	{
	public:
		static void Init();
		static void SetViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
		static void DrawIndexed(const VertexArray& vao);
		static void PollEvents();
		static void SwapBuffers();
	private:
		static std::unique_ptr<Window> _window;
	};
}