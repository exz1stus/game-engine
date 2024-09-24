#pragma once
#include "entt/entt.hpp"
#include "debug/imgui/IDebugMenu.h"
#include "physics/2d/PhysWorld.h"

namespace eng
{
	class Camera;
	class Entity;
	class System;
	class ScriptComponent;

	class Scene : public IDebugMenu
	{
	public:
		void Init();
		Entity AddEntity();
		void RemoveEntity(const Entity id);
		void Update();
		void PhysicsUpdate();
		void Render();

		std::shared_ptr<PhysWorld> GetPhysWorld() const { return _physWorld; }
		std::shared_ptr<Camera> GetMainCamera() const { return _mainCamera; }
		void SetMainCamera(std::shared_ptr<Camera> cam);
	private:
		virtual void DrawMenu() override;
		entt::registry& GetRegistry() { return _registry; }
		entt::registry _registry;
		friend class Entity;
		friend class System;

		std::shared_ptr<Camera> _mainCamera;
		std::shared_ptr<PhysWorld> _physWorld;
	};
}

