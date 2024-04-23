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
		entt::registry _registry;//TODO : private
	private:
		friend class Entity;
	};
}

