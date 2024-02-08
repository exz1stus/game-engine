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
	private:
		 
	};
	Application* CreateApplication();
}

