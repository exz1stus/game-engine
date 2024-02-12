#include "engpch.h"
#include "GameTime.h"
#include "GLFW/glfw3.h"

namespace eng
{
	void GameTime::UpdateGameTime()
	{
		_currentGameTime = glfwGetTime();
		_deltaTime = _currentGameTime - _lastFrameTime;
		_lastFrameTime = _currentGameTime;
	}
	double GameTime::_currentGameTime = 0.0f;
	double GameTime::_deltaTime = 0.0f;
	double GameTime::_lastFrameTime = 0.0f;
}