#pragma once
#include <string>
struct ApplicationVariables
{
#define DEBUG_RENDERDOC 1
 
#if DEBUG_RENDERDOC
	std::string texturesLocation = "../Engine/assets/textures/";
	std::string shadersLocation = "../Engine/assets/shaders/opengl/";
#else
	std::string texturesLocation = "assets/textures/";
	std::string shadersLocation = "assets/shaders/opengl/";
#endif
};

ApplicationVariables& GetVars();

