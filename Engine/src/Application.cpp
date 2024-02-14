#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/RenderingEvents.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"
#include "GameTime.h"

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
		ApplicationEvents::OnInit += GameTime::Init;
		ApplicationEvents::OnInit += Renderer2D::Init;
		ApplicationEvents::OnInit += ImguiManager::Init;
	 
		RenderingEvents::OnWindowClosed.Bind(&Application::Quit, this);
	}
	void Application::MainLoop()
	{
		while (_isRunning)
		{
			ApplicationEvents::OnUpdate();
			ApplicationEvents::OnRender();
		}
	}
	void Application::Quit()
	{
		ApplicationEvents::OnQuit();
		_isRunning = false;
	}
}