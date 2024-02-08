#pragma once

#include "Application.h"

extern eng::Application* eng::CreateApplication();

int main(int argc, char** argv)
{
	auto app = eng::CreateApplication();
	app->MainLoop();
	delete app;

	return 0;
}
