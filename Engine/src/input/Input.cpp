#include "engpch.h"
#include "Input.h"

#include "renderer/platform/opengl/RenderingAPI.h"

namespace eng
{
	static GLFWwindow* window;
	void Input::Init()
	{
		window = glfwGetCurrentContext();
	}
	bool Input::GetKeyDown(KeyCode code)
	{
		return glfwGetKey(window,(int)code) == GLFW_PRESS;
	}
	bool Input::GetKeyUp(KeyCode code)
	{
		return glfwGetKey(window, (int)code) == GLFW_RELEASE;
	}
	bool Input::GetMouseButtonDown(MouseButton button)
	{
		return false;
	}
	bool Input::GetMouseButtonUp(MouseButton button)
	{
		return false;
	}
	glm::vec2 Input::GetMousePos()
	{
		return glm::vec2();
	}
	float Input::GetAxis(Axis axis)
	{
		return 0.0f;
	}
}