#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "events/Event.h"

namespace eng
{
	//TO REMOVE
	float randomFloat(double M, double N)
	{
		return M + (rand() / (RAND_MAX / (N - M)));
	}

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
		while (true)
		{
			for (size_t i = 0; i < 1; i++)
			{
				Renderer2D::DrawQuad({ randomFloat(-300,300), randomFloat(-300,300)}, {100.0f , 100.0f}, { randomFloat(0,1), randomFloat(0,1), randomFloat(0,1), randomFloat(0,1) });
			}
			Renderer2D::EndScene();
		}
	}
}