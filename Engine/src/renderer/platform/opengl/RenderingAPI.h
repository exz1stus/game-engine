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
		static void SetViewport(uint16_t width, uint16_t height);
		static void DrawIndexed(const VertexArray& vao, const uint32_t indexCount = 0);
		static void PollEvents();
		static void SwapBuffers();

		static void SetVSync(bool vsync);
		static std::unique_ptr<Window> _window; //to make private
	private:
		static void WaitForNextFrame();
	};
}