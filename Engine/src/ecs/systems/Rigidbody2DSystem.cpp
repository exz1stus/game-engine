#include "engpch.h"
#include "Rigidbody2DSystem.h"
#include "ecs/CoreComponents.h"
#include "physics/2d/components/Rb2DComponent.h"
namespace eng
{
	void Rigidbody2DSystem::Init()
	{
		GetSceneRegistry().on_construct<Rb2DComponent>().connect<&Rigidbody2DSystem::AttachRigidbody2DCallback>(this);
	}
	void Rigidbody2DSystem::AttachRigidbody2DCallback(entt::registry& registry, Entity entity)
	{
		auto& tr = entity.GetComponent<TransformComponent>();
		entity.GetComponent<Rb2DComponent>().AttachRB(
			SceneManager::GetCurrentScene()->GetPhysWorld()->CreateBody(tr.position, tr.rotation.z)
		);
	}
}