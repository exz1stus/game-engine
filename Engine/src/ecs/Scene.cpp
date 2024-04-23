#include "engpch.h"
#include "Scene.h"
#include "Entity.h"
#include "CoreComponents.h"
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "renderer/Renderer2D.h"

namespace eng
{
	static void RemoveScriptCallback(entt::registry& registry, Entity entity)
	{
		entity.GetComponent<ScriptComponent>().RemoveScript();
	}

	static entt::observer camObserver;

	void Scene::Init()
	{
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
}
