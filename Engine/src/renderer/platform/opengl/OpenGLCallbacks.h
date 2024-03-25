#pragma once
#include <GLFW/glfw3.h>

namespace eng
{
	void WindowResizedCallback(GLFWwindow* window, int width, int height);
	void MouseMovedCallback(GLFWwindow* window, double  xPos, double yPos);
}