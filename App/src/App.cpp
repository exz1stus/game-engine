#include "engpch.h"
#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"


#include "renderer/platform/opengl/Texture2D.h"
#include "misc/ApplicationVariables.h"
#include "ecs/example scripts/PlayerController.h"

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
	Entity e;
	auto& transform = e.AddComponent<TransformComponent>();
	auto& sprite = e.AddComponent<SpriteRendererComponent>();
	
	
	transform.scale.x = 50;
	transform.scale.y = 50;
	sprite.texture = texs[6];

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			Entity e;
			auto& transform = e.AddComponent<TransformComponent>();
			auto& sprite = e.AddComponent<SpriteRendererComponent>();
			e.AddComponent<ScriptComponent>().AddScript<PlayerController>();;
			transform.scale = { 5.0f ,5.0f, 1.0f };
			transform.position.x = i * transform.scale.x;
			transform.position.y = j * transform.scale.y;
			sprite.texture = texs[7];
		}
	}

	

}

void Game::Update()
{
	/*int size = 10;
	for (size_t i = 0; i < 30; i++)
	{
		for (size_t j = 0; j < 30; j++)
		{
			eng::Renderer2D::DrawQuad({ size * i, size * j }, { size , size }, { 1.0f, 1.0f, 1.0f, 1.0f }, texs[7]);
		}
	}*/

	eng::Renderer2D::_cam->SetPosition(glm::vec3(x, y, z));
	eng::Renderer2D::_cam->SetRotation(glm::vec3(rx, ry, rz));
}
