#pragma once
#include "ecs/CoreComponents.h"
#include "ecs/BehaviourScript.h"
namespace eng
{
	class CameraController : public BehaviourScript
	{
	private:
		void OnInit() override;
		void OnUpdate() override;
		void CalculateRotation(float mouseX, float mouseY);
		float speed = 50.0f;
		float freeLookSensitivity = 0.1f;
		cmp_ref<TransformComponent> transform;
	};
}

