#include "engpch.h"
#include "Application.h"
#include "renderer/Renderer2D.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "renderer/RenderingEvents.h"
#include "ApplicationEvents.h"
#include "GameTime.h"
#include "debug/imgui/ImguiManager.h"
#include "assets/AssetManager.h"
#include "ecs/SceneManager.h"

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
		ApplicationEvents::OnInit += SceneManager::Init;
	 
		RenderingEvents::OnWindowClosed.Bind(&Application::Quit, this);
	}
	void Application::MainLoop()
	{
		while (_isRunning)
		{
			ApplicationEvents::OnUpdate();
			Renderer2D::BeginScene();
			ApplicationEvents::OnRender();
			Renderer2D::EndScene();
			test();
		}
	}
	void Application::Quit()
	{
		ApplicationEvents::OnQuit();
		_isRunning = false;
	}
}