#include "engpch.h"
#include "core/EntryPoint.h"
#include "eng.h"
#include "App.h"
#include "ApplicationEvents.h"
#include "debug/imgui/ImguiManager.h"

#include "renderer/platform/opengl/Texture2D.h"
#include "misc/ApplicationVariables.h"
#include "ecs/example scripts/CameraController.h"
#include "PlayerController.h"
#include "ecs/CameraComponent.h"

#include "ecs/component_ref.h"
#include "network/NetworkManager.h"


eng::Application* eng::CreateApplication()
{
	return new Game();
}

static float rx = 0;
static float ry = 0;
static float rz = 0;

static std::array<std::shared_ptr<Texture2D>, 32> texs;

static bool isHost = false;

Game::Game()
	:client(nullptr)
{
	ApplicationEvents::OnRender.Bind(&Game::Update, this);
	for (size_t i = 0; i < texs.size(); i++)
	{
		std::string texPath = GetVars().texturesLocation + std::to_string(i + 1) + ".jpg";
		texs[i] = std::make_shared<eng::Texture2D>(texPath);
	}
	
	std::shared_ptr client = NetworkManager::CreateClient();
	if (!client->Connect("127.0.0.1", 7777))
	{
		NetworkManager::CreateInternalServer();
		client->Connect("127.0.0.1", 7777);
		isHost = true;
	}
	NetworkManager::StartNetworkLoop();

	cam.AddComponent<TransformComponent>().position.z = -10.0f;
	cam.AddComponent<CameraComponent>();

	Entity player;
	player.AddComponent<TransformComponent>();
	player.AddComponent<SpriteRendererComponent>().texture = texs[7];
	player.GetComponent<TransformComponent>().scale = { 20.0f, 20.0f, 0.0f };
	player.AddComponent<ScriptComponent>().AddScript<PlayerController>();
	
	Entity player2;
	player2.AddComponent<TransformComponent>();
	player2.AddComponent<SpriteRendererComponent>().texture = texs[8];
	player2.GetComponent<TransformComponent>().scale = { 20.0f, 20.0f, 0.0f };
	player2.AddComponent<ScriptComponent>().AddScript<PlayerController>();
}

void Game::Start()
{
	Entity player = 1;
	auto& controller = player.GetComponent<ScriptComponent>().GetScript<PlayerController>();

	controller.isMine = isHost;

	Entity player2 = 2;
	auto& controller2 = player2.GetComponent<ScriptComponent>().GetScript<PlayerController>();

	controller2.isMine = !isHost;
}

void Game::Update()
{
	if (!started)
		Start();
}