#pragma once
#include <memory>
#include "Scene.h"
namespace eng
{
	class CameraComponent;
	class Camera;

	class SceneManager
	{
	public:
		static void Init();
		static std::shared_ptr<Scene> GetCurrentScene() { return _currentScene; }
		static std::shared_ptr<Camera> GetMainCamera() { return _mainCamera; }
	private:

		static std::shared_ptr<Scene> _currentScene;
		static std::shared_ptr<Camera> _mainCamera;
		friend class CameraComponent;
	};
}

