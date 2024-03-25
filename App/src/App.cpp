#include "engpch.h"
#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"


#include "renderer/platform/opengl/Texture2D.h"
#include "misc/ApplicationVariables.h"

using namespace eng;

eng::Application* eng::CreateApplication()
{
	return new Game();
}
static float a = 10;
static float x = 10;
static float y = 10;
static float z = 10;

static float rx = 0;
static float ry = 0;
static float rz = 0;


static std::array<std::shared_ptr<Texture2D>, 32> texs;

int ind;

Game::Game()
{
	eng::ApplicationEvents::OnRender.Bind(&Game::Update, this);

	//eng::ImguiManager::AddFloat("123", &a, 1.0f, 1000000.f);
	eng::ImguiManager::AddFloat("123", &x, 0.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &y, 0.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &z, 0.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &rx, 0.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &rz, 0.0f, 1000.0f);
	//eng::ImguiManager::AddFloat("123", &rz, 0.0f, 1000.0f);
	//eng::ImguiManager::AddFloat("4", &b, 0.0f, 1.f);

	for (size_t i = 0; i < texs.size(); i++)
	{
		std::string texPath = GetVars().texturesLocation + std::to_string(i + 1) + ".jpg";
		texs[i] = std::make_shared<eng::Texture2D>(texPath);
	}

}
void Game::Update()
{
	eng::Renderer2D::_cam->SetPosition(glm::vec3(x,y,z));
	eng::Renderer2D::_cam->SetRotation(glm::vec3(rx, ry, rz));

	eng::Renderer2D::BeginScene();

	uint32_t size = 10;

	/*for (size_t x = 0; x < a; x++)
	{
		for (size_t y = 0; y < a; y++)
		{
			eng::Renderer2D::DrawQuad({ size * x, size * y }, { size , size }, { 1.0f, 1.0f, 1.0f, 1.0f }, texs[(x*y)]);
		}
	}*/
	
	
	for (size_t i = 0; i < 33; i++)
	{
		for (size_t j = 0; j < 33; j++)
		{
			ind++;
			if (ind > 2) ind = 0;
			eng::Renderer2D::DrawQuad({ size * i, size * j }, { size , size }, { 1.0f, 1.0f, 1.0f, 1.0f }, texs[ind]);
		}
	}

	//for (size_t j = 0; j < 32*32; j++)
	//{
	//	eng::Renderer2D::DrawQuad({ size * j, size }, { size , size }, { 1.0f, 1.0f, 1.0f, 1.0f }, texs[j % 4]);
	//}
	eng::Renderer2D::EndScene();
}
