#include "engpch.h"
#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"


#include "renderer/platform/opengl/Texture2D.h"
#include "misc/ApplicationVariables.h"
#include "ecs/example scripts/PlayerController.h"
#include "ecs/example scripts/CameraController.h"
#include "ecs/CameraComponent.h"

#include "ecs/component_ptr.h"

using namespace eng;

eng::Application* eng::CreateApplication()
{
	return new Game();
}

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

	eng::ImguiManager::AddFloat("123", &x, 0.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &y, -1000.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &z, -1000.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &rx, -1000.0f, 1000.0f);
	eng::ImguiManager::AddFloat("123", &ry, -1000.0f, 1000.0f);
	//eng::ImguiManager::AddFloat("123", &rz, -1000.0f, 1000.0f);

	for (size_t i = 0; i < texs.size(); i++)
	{
		std::string texPath = GetVars().texturesLocation + std::to_string(i + 1) + ".jpg";
		texs[i] = std::make_shared<eng::Texture2D>(texPath);
	}

	/*auto& transform = e.AddComponent<TransformComponent>();
	auto& sprite = e.AddComponent<SpriteRendererComponent>();

	transform.scale = { 50.0f ,50.0f, 1.0f };
	transform.position.z = -10.0f;
	sprite.texture = texs[7];*/

	cam.AddComponent<TransformComponent>();
	cam.AddComponent<CameraComponent>();
	cam.AddComponent<ScriptComponent>().AddScript<CameraController>();

	auto tr = cam.GetComponentReactive<TransformComponent>();
	//tr->position.z = -20.0f;



	// Entity 1: Front face
	//Entity e;
	e.AddComponent<TransformComponent>();
	e.AddComponent<SpriteRendererComponent>().texture = texs[7];
	e.GetComponent<TransformComponent>().position = { 0.0f, 0.0f, 0.0f };
	e.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	e.GetComponent<TransformComponent>().rotation = { 0.0f, 0.0f, 0.0f };

	Entity entity2;
	entity2.AddComponent<TransformComponent>();
	entity2.AddComponent<SpriteRendererComponent>().texture = texs[7];
	entity2.GetComponent<TransformComponent>().position = { 0.0f, 7.5f, 7.5f };
	entity2.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	entity2.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };

	Entity entity3;
	entity3.AddComponent<TransformComponent>();
	entity3.AddComponent<SpriteRendererComponent>().texture = texs[7];
	entity3.GetComponent<TransformComponent>().position = { 0.0f, -7.5f, 7.5f };
	entity3.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	entity3.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };

	Entity entity4;
	entity4.AddComponent<TransformComponent>();
	entity4.AddComponent<SpriteRendererComponent>().texture = texs[7];
	entity4.GetComponent<TransformComponent>().position = { 0.0f, 0.0f, 15.0f };
	entity4.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 0.0f };
	entity4.GetComponent<TransformComponent>().rotation = { 0.0f, 0.0f, 0.0f };


	marker.AddComponent<TransformComponent>();
	marker.AddComponent<SpriteRendererComponent>().texture = texs[8];

	marker.GetComponent<TransformComponent>().scale = { 50.0f, 50.0f, 1.0f };


	/*for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 1; j++)
		{
			Entity e;
			auto& transform = e.AddComponent<TransformComponent>();
			auto& sprite = e.AddComponent<SpriteRendererComponent>();
			e.AddComponent<ScriptComponent>().AddScript<CameraController>();
			transform.scale = { 5.0f ,5.0f, 1.0f };
			transform.position.x = i * transform.scale.x;
			transform.position.y = j * transform.scale.y;
			sprite.texture = texs[7];
		}
	}*/
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
	auto tr = cam.GetComponentReactive<TransformComponent>();

}
