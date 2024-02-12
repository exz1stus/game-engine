#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/RenderingEvents.h"
#include "ApplicationEvents.h"

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
		SubsribeStaticClasses();
		ApplicationEvents::OnInit();
	}

	void Application::SubsribeStaticClasses()
	{
		ApplicationEvents::OnInit += Renderer2D::Init;

		RenderingEvents::OnWindowClosed.Bind(&Application::Quit, this);
	}
	void Application::MainLoop()
	{
		while (_isRunning)
		{
			ApplicationEvents::OnUpdate();
			ApplicationEvents::OnRender();

			//
			for (size_t i = 0; i < 1; i++)
			{
				Renderer2D::DrawQuad({ 0,0 }, { 100.0f , 100.0f }, { 1.0f, 0.5f, 1.0f, 1.0f});
				//Renderer2D::DrawQuad({ 150,0 }, { 100.0f , 100.0f }, { 0.5f, 1.0f, 0.5f, 1.0f });
			}

			Renderer2D::EndScene();
		}
	}
	void Application::Quit()
	{
		ApplicationEvents::OnQuit();
		_isRunning = false;
	}
}