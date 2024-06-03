#include "engpch.h"
#include "Scene.h"
#include "Entity.h"
#include "CoreComponents.h"
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "renderer/Renderer2D.h"
#include "debug/imgui/ImguiManager.h"

namespace eng
{
	static void RemoveScriptCallback(entt::registry& registry, Entity entity)
	{
		entity.GetComponent<ScriptComponent>().RemoveScript();
	}

	static entt::observer camObserver;

	void Scene::Init()
	{
		ImguiManager::AddMenu(this);
		_registry.on_destroy<ScriptComponent>().connect<&RemoveScriptCallback>();
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
		for (Entity entity : camObserver)
		{
			entity.GetComponent<CameraComponent>().UpdateCameraTransform(entity.GetComponent<TransformComponent>());
		}
		camObserver.clear();

		auto view = _registry.view<ScriptComponent>();

		for (Entity entity : view)
		{
			auto& script = entity.GetComponent<ScriptComponent>();

			if (!script._scriptInstance)
			{
				script._scriptInstance = script.InstantiateFunction();
				script._scriptInstance->id = entity;
				script._scriptInstance->OnInit();
			}
			script._scriptInstance->OnUpdate();
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
	void Scene::DrawMenu()
	{
		SetMenuName("Scene Inspector");		

		auto view = _registry.view<TransformComponent>();
		//ImGui::Text("asd");
		ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, -FLT_MIN/*5 * ImGui::GetTextLineHeightWithSpacing()*/));
		//ImGui::BeginListBox("Entities");
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
