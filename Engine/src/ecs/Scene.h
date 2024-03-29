#pragma once
#include "entt/entt.hpp"

namespace eng
{
	class Entity;
	class Scene
	{
	public:
		void Init();
		Entity AddEntity();
		void RemoveEntity(const Entity id);
		void Update();
		void Render();
	private:
		entt::registry _registry;
		friend class Entity;
	};
}

