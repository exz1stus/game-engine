#include "engpch.h"
#include "CameraController.h"

#include <GLFW/glfw3.h>
#include "renderer/Camera.h"
#include "GameTime.h"
#include "input/InputEvents.h"

#include "misc/Utilities.h"


namespace eng
{
	void CameraController::OnInit()
	{
		transform = GetComponentReactive<TransformComponent>();
		InputEvents::OnMouseMoved.Bind(&CameraController::CalculateRotation,this);
	}
	void CameraController::OnUpdate()
	{
		glm::vec3 movement = glm::vec3(0);

		auto wind = glfwGetCurrentContext();

		if (glfwGetKey(wind, GLFW_KEY_W)) movement += transform.get_readonly()->GetForward();
		if (glfwGetKey(wind, GLFW_KEY_S)) movement -= transform.get_readonly()->GetForward();
		if (glfwGetKey(wind, GLFW_KEY_D)) movement += transform.get_readonly()->GetRight();
		if (glfwGetKey(wind, GLFW_KEY_A)) movement -= transform.get_readonly()->GetRight();
		if (glfwGetKey(wind, GLFW_KEY_SPACE)) movement += transform.get_readonly()->GetUp();
		if (glfwGetKey(wind, GLFW_KEY_LEFT_SHIFT)) movement -= transform.get_readonly()->GetUp();

		if (movement.x != 0 && movement.y != 0) movement = glm::normalize(movement);

		if (glm::length(movement) > 0.0f)
		{
			movement = glm::normalize(movement) * speed * (float)GameTime::GetDeltaTime();
			transform->position += movement;
		}
	}
	
	void CameraController::CalculateRotation(float mouseX, float mouseY)
	{
		glm::vec3& cameraRot = transform->rotation;

		static float lastX = 0.0f;
		static float lastY = 0.0f;
		float deltaX = mouseX - lastX;
		float deltaY = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;

		float yaw = deltaX * freeLookSensitivity;
		float pitch = deltaY * freeLookSensitivity;

		cameraRot.y -= yaw;
		cameraRot.x += pitch;

		const float maxPitch = 89.0f;
		if (cameraRot.x > maxPitch)
			cameraRot.x = maxPitch;
		else if (cameraRot.x < -maxPitch)
			cameraRot.x = -maxPitch;
	}
}