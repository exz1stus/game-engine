#include "engpch.h"
#include "OpenGLCallbacks.h"
#include "../RenderingEvents.h"

namespace eng
{
	void WindowResizedCallback(GLFWwindow* window, int width, int height)
	{
		RenderingEvents::OnWindowResized(width, height);
	}
}