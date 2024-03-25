#include "engpch.h"
#include "OpenGLCallbacks.h"
#include "renderer/RenderingEvents.h"

namespace eng
{
	//TODO : bind directly to invoke without boilerplate functions
	void WindowResizedCallback(GLFWwindow* window, int width, int height)
	{
		RenderingEvents::OnWindowResized(width, height);
	}
	void MouseMovedCallback(GLFWwindow* window, double xPos, double yPos)
	{

	}
}