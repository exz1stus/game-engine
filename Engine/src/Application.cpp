#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/platform/opengl/RenderingAPI.h"

namespace eng
{

	Application::Application()
	{
		Init();
	}
	void Application::Init()
	{
		Renderer2D::Init();
	}
	void Application::MainLoop()
	{
		float i = 0;
		while (true)
		{
			Renderer2D::DrawQuad({0.0f + i, 0.0f}, {1.0f + i, 1.0f + i}, {1.0f, 1.0f, 1.0f, 1.0f});
			i += 0.01f;
		}
	}

}