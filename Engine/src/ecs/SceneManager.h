#pragma once
#include <memory>
#include "Scene.h"
#include "physics/2d/PhysWorld.h"
namespace eng
{
	class CameraComponent;
	class Camera;

	class SceneManager
	{
	public:
		static void Init();
		static std::shared_ptr<Scene> GetCurrentScene() { return _currentScene; }
	private:
		static std::shared_ptr<Scene> _currentScene;
	};
}

