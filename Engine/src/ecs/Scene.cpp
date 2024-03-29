#include "engpch.h"
#include "Scene.h"
#include "Entity.h"
#include "CoreComponents.h"
#include "ScriptComponent.h"
#include "renderer/Renderer2D.h"

namespace eng
{
	void Scene::Init()
	{}

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
		auto view = _registry.view<ScriptComponent>();

		for (Entity entity : view)
		{
			auto& script = entity.GetComponent<ScriptComponent>();

			if (!script._scriptInstance)
			{
				script._scriptInstance = script.InstantiateFunction();
				script._scriptInstance->OnInit();
				script._scriptInstance->id = entity;
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
				transform.position,
				transform.scale,
				sprite.GetRGBA(), sprite.texture);
		}
	}
}
