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

static float rx = 0;
static float ry = 0;
static float rz = 0;

static std::array<std::shared_ptr<Texture2D>, 32> texs;

Game::Game()
{
	ApplicationEvents::OnRender.Bind(&Game::Update, this);

	for (size_t i = 0; i < texs.size(); i++)
	{
		std::string texPath = GetVars().texturesLocation + std::to_string(i + 1) + ".jpg";
		texs[i] = std::make_shared<eng::Texture2D>(texPath);
	}

	cam.AddComponent<TransformComponent>();
	cam.AddComponent<CameraComponent>();
	cam.AddComponent<ScriptComponent>().AddScript<CameraController>();

	//Entity e;
	e.AddComponent<TransformComponent>();
	e.AddComponent<SpriteRendererComponent>().texture = texs[7];
	e.GetComponent<TransformComponent>().position = { 0.0f, 0.0f, 0.0f };
	e.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	e.GetComponent<TransformComponent>().rotation = { 0.0f, 0.0f, 0.0f };

	Entity entity2;
	entity2.AddComponent<TransformComponent>();
	entity2.AddComponent<SpriteRendererComponent>().texture = texs[8];
	entity2.GetComponent<TransformComponent>().position = { 0.0f, 7.5f, 7.5f };
	entity2.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	entity2.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };

	Entity entity3;
	entity3.AddComponent<TransformComponent>();
	entity3.AddComponent<SpriteRendererComponent>().texture = texs[9];
	entity3.GetComponent<TransformComponent>().position = { 0.0f, -7.5f, 7.5f };
	entity3.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	entity3.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };

	Entity entity4;
	entity4.AddComponent<TransformComponent>();
	entity4.AddComponent<SpriteRendererComponent>().texture = texs[10];
	entity4.GetComponent<TransformComponent>().position = { 0.0f, 0.0f, 15.0f };
	entity4.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 0.0f };
	entity4.GetComponent<TransformComponent>().rotation = { 0.0f, 0.0f, 0.0f };

	rotX.AddComponent<TransformComponent>().position = { 30.0f, 0.0f,0.0f };
	rotY.AddComponent<TransformComponent>().position = { 60.0f, 0.0f,0.0f };
	rotZ.AddComponent<TransformComponent>().position = { 90.0f, 0.0f,0.0f };

	rotX.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };
	rotY.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };
	rotZ.GetComponent<TransformComponent>().rotation = { 90.0f, 0.0f, 0.0f };

	rotX.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	rotY.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };
	rotZ.GetComponent<TransformComponent>().scale = { 15.0f, 15.0f, 1.0f };

	rotX.AddComponent<SpriteRendererComponent>().texture = texs[15];
	rotY.AddComponent<SpriteRendererComponent>().texture = texs[15];
	rotZ.AddComponent<SpriteRendererComponent>().texture = texs[15];

	/*for (size_t x = 0; x < 100; x++)
	{
		for (size_t y = 0; y < 100; y++)
		{
			Entity e;
			e.AddComponent<TransformComponent>().position = { x * 50, y*50,0.0f };
			e.GetComponent<TransformComponent>().scale = { 50, 50,1.0f };
			e.AddComponent<SpriteRendererComponent>().texture = texs[17];
		}
	}*/

}

void Game::Update()
{
	rotX.GetComponent<TransformComponent>().rotation.x += 100.0f * GameTime::GetDeltaTime();
	rotY.GetComponent<TransformComponent>().rotation.y += 100.0f * GameTime::GetDeltaTime();
	rotZ.GetComponent<TransformComponent>().rotation.z += 100.0f * GameTime::GetDeltaTime();

	Logger::Log("AAA");
	Logger::Warning("AAA");
	Logger::Error("AAA");
	Logger::CriticalError("AAA");
}
