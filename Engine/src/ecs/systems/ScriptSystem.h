#pragma once
#include "ecs/System.h"
namespace eng
{
	class ScriptSystem : public System
	{
	public:
		void Init() override;
	private:
		void Update();
		void InstantiateScripts(Entity id, ScriptComponent& script);
		void RemoveScriptCallback(entt::registry& registry, Entity entity);
	};
}

