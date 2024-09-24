#include "engpch.h"
#include "core/EntryPoint.h"
#include "single_test.h"
#include "debug/imgui/ImguiManager.h"

#include "core/eng.h"

#include "physics/2d/components/Physics2DComponents.h"

eng::Application* eng::CreateApplication()
{
	return new Game();
}

static std::array<std::shared_ptr<Texture2D>, 32> texs;

Game::Game()
{
	ApplicationEvents::OnUpdate.Bind(&Game::Update, this);
	for (size_t i = 0; i < texs.size(); i++)
	{
		std::string texPath = GetVars().texturesLocation + std::to_string(i + 1) + ".jpg";
		texs[i] = std::make_shared<eng::Texture2D>(texPath);
	}

	cam.AddComponent<TransformComponent>();
	cam.AddComponent<CameraComponent>();

	Event e;
}

bool started = false;

static void CreateEntity()
{
	static int entCount = 0;

	Entity ent;
	auto& tr = ent.AddComponent<TransformComponent>();
	tr.scale = { 5.0f, 5.0f, 1.0f };
	tr.position = { entCount % 100 * tr.scale.x , (int)(entCount / 100) * tr.scale.y, 0.0f };
	ent.AddComponent<SpriteRendererComponent>().texture = texs[12];
	entCount++;
	ent.AddComponent<Rb2DComponent>();
	ent.AddComponent<BoxCollider2DComponent>();
}

static void Draw()
{
	static int entCount = 0;

	glm::vec3 scale = { 5.0f, 5.0f, 1.0f };
	glm::vec3 position = { entCount % 100 * scale.x , (int)(entCount / 100) * scale.y, 0.0f };

	Renderer2D::DrawQuad(position, scale, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), texs[1]);
	entCount++;
}

void Game::Start()
{
	started = true;

	e.AddComponent<TransformComponent>().scale = { 50.0f, 50.0f, 1.0f};
	e.AddComponent<SpriteRendererComponent>().texture = texs[12];
	e.AddComponent<Rb2DComponent>();
	e.AddComponent<BoxCollider2DComponent>();
}

void Game::Update()
{
	if (!started)
		Start();

	if (Input::GetKeyDown(KeyCode::KEY_0))
	{
		e.GetComponent<Rb2DComponent>().AddForce({ 22.0f, 0.0f });
	}
	if (Input::GetKeyDown(KeyCode::KEY_1))
	{
		e.GetComponent<TransformComponent>().position = { 0.0f, 0.0f, 0.0f };
	}
}