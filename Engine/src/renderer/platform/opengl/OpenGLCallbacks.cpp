#include "engpch.h"
#include "OpenGLCallbacks.h"
#include "renderer/RenderingEvents.h"
#include "input/InputEvents.h"

namespace eng
{
	void WindowResizedCallback(GLFWwindow* window, int width, int height)
	{
		RenderingEvents::OnWindowResized(width, height);
	}
	void MouseMovedCallback(GLFWwindow* window, double xPos, double yPos)
	{
		InputEvents::OnMouseMoved(xPos, yPos);
	}
}