#pragma once
namespace eng
{
	enum class RunningMode
	{
		GUIApplication,
		Headless
	};

	class Application
	{
	public:
		Application(RunningMode mode = RunningMode::GUIApplication);

		void Init();
		void MainLoop();
		void Quit();
	private:
		bool _isRunning = true;
		RunningMode _mode;
		void SubscribeStaticClasses();
	};
	Application* CreateApplication();
}

