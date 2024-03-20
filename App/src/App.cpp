#include "engpch.h"
#include "App.h"

eng::Application* eng::CreateApplication()
{
	return new Game();
}
