#pragma once
#include "renderer/Camera.h"

namespace eng
{
	struct CameraComponent 
	{
		CameraComponent();
		void UpdateCameraTransform(const TransformComponent& transform);
		void SetMain();
	private:
		std::shared_ptr<Camera> _cam;
	};
} 