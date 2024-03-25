#include "engpch.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "renderer/Renderer2D.h"
#include "Utilities.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	void test()
	{
		Window* window = RenderingAPI::_window.get();
		Camera* cam = Renderer2D::_cam.get();

		const float cameraSpeed = 0.5f;
		if (window->GetKey(GLFW_KEY_W) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + cameraSpeed * glm::vec3(0.0f,0.0f,-1.0f));
		if (window->GetKey(GLFW_KEY_S) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f));
		if (window->GetKey(GLFW_KEY_A) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f) * cameraSpeed);
		if (window->GetKey(GLFW_KEY_D) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * cameraSpeed);
		if (window->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f));
		if (window->GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cam->SetPosition(cam->GetPosition() + cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f));
	}
}