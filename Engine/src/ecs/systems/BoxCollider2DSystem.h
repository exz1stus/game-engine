#pragma once
#include "ecs/System.h"
namespace eng
{
	class BoxCollider2DSystem : public System
	{
	public:
		void Init() override;
	private:
		void AttachBoxCollider2DCallback(entt::registry& registry, Entity entity);
	};
}

