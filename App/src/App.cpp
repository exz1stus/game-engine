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

#include "network/components/NetTransformComponent.h"
#include "network/components/NetSpriteRenderer.h"
#include "ecs/component_ref.h"
#include "network/NetworkManager.h"

#include "input/Input.h"

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
	//cam.AddComponent<ScriptComponent>().AddScript<FreeFlyCameraController>();

	Entity player1;
	player1.AddComponent<TransformComponent>();
	player1.AddComponent<SpriteRendererComponent>().texture = texs[8];
	player1.GetComponent<TransformComponent>().scale = { 50.0f, 50.0f, 0.0f };
	auto& scriptHodler1 = player1.AddComponent<ScriptComponent>();
	scriptHodler1.AddScript<PlayerController>();
	scriptHodler1.AddScript<NetTransform>();
	scriptHodler1.AddScript<NetSpriteRenderer>();

	Entity player2;
	player2.AddComponent<TransformComponent>();
	player2.AddComponent<SpriteRendererComponent>().texture = texs[2];
	player2.GetComponent<TransformComponent>().scale = { 50.0f, 50.0f, 0.0f };
	auto& scriptHodler2 = player2.AddComponent<ScriptComponent>();
	scriptHodler2.AddScript<PlayerController>();
	scriptHodler2.AddScript<NetTransform>();
	scriptHodler2.AddScript<NetSpriteRenderer>();
}

void Game::Start()
{
	started = true;

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
	
	if (Input::GetKeyDown(KeyCode::KEY_0))
	{
		Entity player = 1;
		auto& sprite = player.GetComponent<ScriptComponent>().GetScript<NetSpriteRenderer>();
		*sprite.color = { 0.1f , 0.1f, 1.0f };
	}
}