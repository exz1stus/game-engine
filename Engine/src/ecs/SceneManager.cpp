#include "engpch.h"
#include "SceneManager.h"
#include "ApplicationEvents.h"

namespace eng
{
	std::shared_ptr<Scene> SceneManager::_currentScene;
	std::shared_ptr<Camera> SceneManager::_mainCamera;
	void SceneManager::Init()
	{
		_currentScene = std::make_shared<Scene>();
		_currentScene->Init();
		ApplicationEvents::OnUpdate.Bind(&Scene::Update, &*_currentScene);
		ApplicationEvents::OnRender.Bind(&Scene::Render, &*_currentScene);
	}
}