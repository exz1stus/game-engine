#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "events/Event.h"

namespace eng
{
	void test();
	Application::Application()
	{
		Init();
		test();
	}
	void Application::Init()
	{
		//module::app::OnInit();
		Renderer2D::Init();
	}

	void Application::MainLoop()
	{
		double deltaTime;
		double time;
		while (true)
		{
			//module::app::OnUpdate();
			//module::app::OnRender();
			
			time = glfwGetTime();
			for (size_t i = 0; i < 1; i++)
			{
				Renderer2D::DrawQuad({ 0,0 }, { 100.0f , 100.0f }, { 1, 0.5f, 1, 1 });
				Renderer2D::DrawQuad({ 150,0 }, { 100.0f , 100.0f }, { 0.5f, 1, 0.5f, 1 });
			}
			deltaTime = time - glfwGetTime();

			//std::cout << deltaTime << std::endl;

			Renderer2D::EndScene();
		}
	}
}