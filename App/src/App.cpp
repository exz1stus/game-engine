//#include "engpch.h"
#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"

eng::Application* eng::CreateApplication()
{
	return new Game();
}

Game::Game()
{
	eng::ApplicationEvents::OnUpdate.Bind(&Game::Update, this);
}
void Game::Update()
{
	for (size_t i = 0; i < 1; i++)
	{
		eng::Renderer2D::DrawQuad({ 0,0 }, { 100.0f , 100.0f }, { 1.0f, 0.5f, 1.0f, 1.0f });
	}

	eng::Renderer2D::EndScene();
}
