#include "engpch.h"
#include "engpch.h"
#include "SceneManager.h"
#include "ApplicationEvents.h"

namespace eng
{
	std::shared_ptr<Scene> SceneManager::_currentScene;
	void SceneManager::Init()
	{
		_currentScene = std::make_shared<Scene>();
		_currentScene->Init();
		ApplicationEvents::OnUpdate.Bind(&Scene::Update, _currentScene.get());
		ApplicationEvents::OnRender.Bind(&Scene::Render, _currentScene.get());
	}
}