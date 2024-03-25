#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "renderer/RenderingEvents.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"
#include "GameTime.h"
#include "assets/AssetManager.h"

namespace eng
{
	void test();
	Application::Application()
	{
		Init();
	}
	void Application::Init()
	{
		SubscribeStaticClasses();
		ApplicationEvents::OnInit();
	}

	void Application::SubscribeStaticClasses()
	{
		ApplicationEvents::OnInit += Logger::Init;
		ApplicationEvents::OnInit += GameTime::Init;
		ApplicationEvents::OnInit += RenderingAPI::Init;
		ApplicationEvents::OnInit += AssetManager::Init;
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

			test();
		}
	}
	void Application::Quit()
	{
		ApplicationEvents::OnQuit();
		_isRunning = false;
	}
}