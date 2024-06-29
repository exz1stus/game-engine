#include "engpch.h"
#include "CameraComponent.h"


namespace eng
{
	CameraComponent::CameraComponent()
		: _cam(nullptr)
	{
		_cam = std::make_shared<Camera>(-350, 350, -300, 300, CameraProjection::PERSPECTIVE);
		if (!SceneManager::GetMainCamera())
			SceneManager::_mainCamera = _cam;
	}
	void CameraComponent::UpdateCameraTransform(const TransformComponent& transform)
	{
		_cam->SetTransform(transform);
	}
}