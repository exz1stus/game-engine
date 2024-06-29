#pragma once
#include "entt/entt.hpp"
#include "debug/imgui/IDebugMenu.h"


namespace eng
{
	class Entity;
	class Scene : public IDebugMenu
	{
	public:
		void Init();
		Entity AddEntity();
		void RemoveEntity(const Entity id);
		void Update();
		void Render();
	private:
		virtual void DrawMenu() override;
		entt::registry _registry;
		friend class Entity;
	};
}

