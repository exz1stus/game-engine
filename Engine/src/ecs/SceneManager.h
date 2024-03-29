#pragma once
#include <memory>
#include "Scene.h"
namespace eng
{
	class SceneManager
	{
	public:
		static void Init();
		static std::shared_ptr<Scene> GetCurrentScene() { return _currentScene; }
	private:
		static std::shared_ptr<Scene> _currentScene;
	};
}

