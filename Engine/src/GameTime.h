#pragma once

namespace eng
{
	class GameTime
	{
	public:
		static void UpdateGameTime();

		static double GetDeltaTime() { return _deltaTime; }
		static double GetTime() { return _currentGameTime; }
	private:
		static double _deltaTime;
		static double _currentGameTime;
		static double _lastFrameTime;
	};
}

