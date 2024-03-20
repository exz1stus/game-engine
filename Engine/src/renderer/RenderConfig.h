#pragma once
#include <string>

namespace eng
{
	struct RenderConfig
	{
		std::string WindowName;
		uint16_t WindowWidth;
		uint16_t WindowHeight;

		uint16_t TargetFPS;
		bool Vsync;
	};

	const RenderConfig& GetRenderConfig();
}