#pragma once
#include <vector>

namespace eng
{
	class Application
	{
	public:
		Application();

		void Init();
		void MainLoop();
		void Quit();
	private:
		bool _isRunning = true;
		void SubsribeStaticClasses();
	};
	Application* CreateApplication();
}

