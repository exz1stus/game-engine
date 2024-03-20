#include "engpch.h"
#include "GameTime.h"
#include "GLFW/glfw3.h"
#include "ApplicationEvents.h"
#include <chrono>

namespace eng
{
	void GameTime::Init()
	{
		ApplicationEvents::OnUpdate += UpdateGameTime;
	}
	void GameTime::UpdateGameTime()
	{
		_currentGameTime = glfwGetTime();
		_deltaTime = _currentGameTime - _lastFrameTime;
		_lastFrameTime = _currentGameTime;
	}
	void GameTime::Sleep(double milliseconds)
	{
		
	}
	double GameTime::_currentGameTime = 0.0f;
	double GameTime::_deltaTime = 0.0f;
	double GameTime::_lastFrameTime = 0.0f;
}