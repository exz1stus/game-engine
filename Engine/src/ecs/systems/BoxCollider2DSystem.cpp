#include "engpch.h"
#include "BoxCollider2DSystem.h"
#include "physics/2d/components/BoxCollider2DComponent.h"
#include "physics/2d/components/Rb2DComponent.h"
#include "ecs/CoreComponents.h"
namespace eng
{
	void BoxCollider2DSystem::Init()
	{
		GetSceneRegistry().on_construct<BoxCollider2DComponent>().connect<&BoxCollider2DSystem::AttachBoxCollider2DCallback>(this);
	}

	void BoxCollider2DSystem::AttachBoxCollider2DCallback(entt::registry& registry, Entity entity)
	{
		auto rb = entity.GetComponent<Rb2DComponent>()._body;
		auto& tr = entity.GetComponent<TransformComponent>();

		entity.GetComponent<BoxCollider2DComponent>()._collider = std::make_unique<BoxCollider2D>(*rb, glm::vec2(tr.scale.x, tr.scale.y));
	}
}