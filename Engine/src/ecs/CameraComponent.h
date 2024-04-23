#pragma once
#include "renderer/Camera.h"
#include "CoreComponents.h"

namespace eng
{
	struct CameraComponent 
	{
		CameraComponent();
		void UpdateCameraTransform(const TransformComponent& transform);
	private:
		std::shared_ptr<Camera> _cam;
	};
} 