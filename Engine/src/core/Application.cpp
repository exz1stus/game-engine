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
#include "network/NetworkManager.h"

namespace eng
{

	Application::Application(RunningMode mode)
		:_mode(mode)
	{
		Init();
	}
	void Application::Init()
	{
		//Logger::Init();
		SubscribeStaticClasses();
		ApplicationEvents::OnInit();
	}

	void Application::SubscribeStaticClasses()
	{
		ApplicationEvents::OnInit += Logger::Init;
		ApplicationEvents::OnInit += GameTime::Init;

		if (_mode == RunningMode::GUIApplication)
		{
			ApplicationEvents::OnInit += RenderingAPI::Init;
			ApplicationEvents::OnInit += AssetManager::Init;
			ApplicationEvents::OnInit += Renderer2D::Init;
			ApplicationEvents::OnInit += ImguiManager::Init;
			RenderingEvents::OnWindowClosed.Bind(&Application::Quit, this);
		}

		ApplicationEvents::OnInit += SceneManager::Init;
		ApplicationEvents::OnInit += NetworkManager::Init;
	

		ApplicationEvents::OnQuit += NetworkManager::Quit;
	}

	void Application::MainLoop()
	{
		while (_isRunning)
		{
			ApplicationEvents::OnUpdate();

			if (_mode == RunningMode::GUIApplication)
			{
				Renderer2D::BeginScene();
				ApplicationEvents::OnRender();
				Renderer2D::EndScene();
			}
		}
	}
	void Application::Quit()
	{
		ApplicationEvents::OnQuit();
		_isRunning = false;
	}
}