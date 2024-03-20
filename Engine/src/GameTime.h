#pragma once

namespace eng
{
	class GameTime
	{
	public:
		static void Init();
		static double GetDeltaTime() { return _deltaTime; }
		static double GetTime() { return _currentGameTime; }
		static void Sleep(double milliseconds);
	private:
		static void UpdateGameTime();
		static double _deltaTime;
		static double _currentGameTime;
		static double _lastFrameTime;
	};
}

