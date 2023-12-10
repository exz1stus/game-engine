#pragma once
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

