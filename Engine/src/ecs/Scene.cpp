#include "engpch.h"
#include "Scene.h"
#include "Entity.h"
#include "CoreComponents.h"
#include "renderer/Renderer2D.h"
#include "debug/imgui/ImguiManager.h"

#include "physics/2d/components/Rb2DComponent.h"
namespace eng
{
	static entt::observer camObserver;

	void Scene::Init()
	{
		ImguiManager::AddMenu(this);

		PhysWorldProperties physProps;
		physProps.g = glm::vec2(0.0f, -9.81f);
		_physWorld = std::make_shared<PhysWorld>(physProps);
		
		camObserver.connect(_registry, entt::collector.update<TransformComponent>().where<CameraComponent>());
	}

	Entity Scene::AddEntity()
	{
		return _registry.create();
	}

	void Scene::RemoveEntity(const Entity id)
	{
		_registry.destroy(id);
	}

	void Scene::Update()
	{
		PhysicsUpdate();

		for (Entity entity : camObserver)
		{
			entity.GetComponent<CameraComponent>().UpdateCameraTransform(entity.GetComponent<TransformComponent>());
		}
		camObserver.clear();
	}

	void Scene::PhysicsUpdate()
	{
		_physWorld->PhysTick();

		auto view = _registry.view<Rb2DComponent, TransformComponent>();

		for (Entity entity : view)
		{
			auto tr = entity.GetComponentReactive<TransformComponent>();
			auto pos = entity.GetComponent<Rb2DComponent>().GetPhysPosition();
			auto rot = entity.GetComponent<Rb2DComponent>().GetPhysRotation();

			tr->position = { pos.x, pos.y, tr->position.z };
			tr->rotation = { tr->rotation.x, tr->rotation.y, rot };
		}
	}

	void Scene::Render()
	{
		auto view = _registry.view<TransformComponent, SpriteRendererComponent>();

		for (const Entity entity : view)
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteRendererComponent>();

			Renderer2D::DrawQuad(
				transform.GetTransform(),
				sprite.GetRGBA(), sprite.texture);
		}
	}

	void Scene::SetMainCamera(std::shared_ptr<Camera> cam)
	{
		_mainCamera = cam;
	}

	void Scene::DrawMenu()
	{
		SetMenuName("Scene Inspector");

		auto view = _registry.view<TransformComponent>();
		ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, -FLT_MIN/*5 * ImGui::GetTextLineHeightWithSpacing()*/));
		for (Entity e : view)
		{
			ImGui::Text("Entity: %i", (int)e);
			auto& tr = e.GetComponent<TransformComponent>();
			ImGui::Text((std::to_string(tr.position.x) + " " + std::to_string(tr.position.y) + " " + std::to_string(tr.position.z)).c_str());
			ImGui::Text((std::to_string(tr.rotation.x) + " " + std::to_string(tr.rotation.y) + " " + std::to_string(tr.rotation.z)).c_str());
			ImGui::Text((std::to_string(tr.scale.x) + " " + std::to_string(tr.scale.y) + " " + std::to_string(tr.scale.z)).c_str());
		}
		ImGui::EndListBox();
	}
}
