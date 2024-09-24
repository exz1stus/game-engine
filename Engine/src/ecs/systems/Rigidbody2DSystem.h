#pragma once
#include "ecs/System.h"
namespace eng
{
	class Rigidbody2DSystem : public System
	{
	public:
		void Init() override;
	private:
		void AttachRigidbody2DCallback(entt::registry& registry, Entity entity);
	};
}

