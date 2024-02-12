//#include "engpch.h"
#include "eng.h"
#include "App.h"

eng::Application* eng::CreateApplication()
{
	return new Game();
}
