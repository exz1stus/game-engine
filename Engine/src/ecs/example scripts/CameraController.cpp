#include "engpch.h"
#include "CameraController.h"

#include <GLFW/glfw3.h>
#include "renderer/Camera.h"
#include "GameTime.h"
#include "input/InputEvents.h"
#include "input/Input.h"

#include "misc/Utilities.h"


namespace eng
{
	void FreeFlyCameraController::OnInit()
	{
		transform = GetComponentReactive<TransformComponent>();
		InputEvents::OnMouseMoved.Bind(&FreeFlyCameraController::CalculateRotation, this);
	}
	void FreeFlyCameraController::OnUpdate()
	{
		glm::vec3 movement = glm::vec3(0);

		if (Input::GetKeyDown(KeyCode::KEY_W)) movement += transform.get().GetForward();
		if (Input::GetKeyDown(KeyCode::KEY_S)) movement -= transform.get().GetForward();
		if (Input::GetKeyDown(KeyCode::KEY_D)) movement += transform.get().GetRight();
		if (Input::GetKeyDown(KeyCode::KEY_A)) movement -= transform.get().GetRight();
		if (Input::GetKeyDown(KeyCode::KEY_SPACE)) movement += transform.get().GetUp();
		if (Input::GetKeyDown(KeyCode::KEY_LEFT_SHIFT)) movement -= transform.get().GetUp();

		if (Input::GetKeyDown(KeyCode::KEY_Q)) transform->rotation.z -= 100.0f*GameTime::GetDeltaTime();
		if (Input::GetKeyDown(KeyCode::KEY_E)) transform->rotation.z += 100.0f*GameTime::GetDeltaTime();

		if (movement.x != 0 && movement.y != 0) movement = glm::normalize(movement);

		if (glm::length(movement) > 0.0f)
		{
			movement = glm::normalize(movement) * speed * (float)GameTime::GetDeltaTime();
			transform->position += movement;
		}
	}

	void FreeFlyCameraController::CalculateRotation(float mouseX, float mouseY)
	{
		glm::vec3& cameraRot = transform->rotation;
		
		float deltaX = mouseX - lastMouseX;
		float deltaY = lastMouseY - mouseY;
		lastMouseX = mouseX;
		lastMouseY = mouseY;

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