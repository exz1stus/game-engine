#pragma once
#include "Entity.h"
#include "SceneManager.h"
namespace eng
{
	class System
	{
	public:
		virtual void Init() = 0;
		entt::registry& GetSceneRegistry() const { return SceneManager::GetCurrentScene()->GetRegistry(); }
	};
}