#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"

#include "debug/imgui/ImguiManager.h"

eng::Application* eng::CreateApplication()
{
	return new Game();
}
static float a = 100;
static float b = 100;

Game::Game()
{
	eng::ApplicationEvents::OnRender.Bind(&Game::Update, this);

	eng::ImguiManager::AddFloat("123", &a, 1.0f, 1000000.f);
	eng::ImguiManager::AddFloat("4", &b, 0.0f, 1.f);
}
void Game::Update()
{
	eng::Renderer2D::BeginScene();

	for (size_t x = 0; x <a; x++)
	{
		for (size_t y = 0; y < a; y++)
		{
			eng::Renderer2D::DrawQuad({15.0f * x , 15.0f * y}, { 15.0f , 15.0f }, { 1.0f,1.0f,b, 1.0f });
		}
	}
	eng::Renderer2D::EndScene();
}
