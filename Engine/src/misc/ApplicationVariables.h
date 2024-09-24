#pragma once
#include <string>
struct ApplicationVariables
{
	std::string texturesLocation = "assets/textures/";
	std::string shadersLocation = "assets/shaders/opengl/";
};

ApplicationVariables& GetVars();

