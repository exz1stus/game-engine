#include "engpch.h"
#include "CameraComponent.h"
#include "ecs/SceneManager.h"


namespace eng
{
	CameraComponent::CameraComponent()
		: _cam(nullptr)
	{
		_cam = std::make_shared<Camera>(-350, 350, -300, 300, CameraProjection::ORTHOGRAPHIC);
		if (!SceneManager::GetCurrentScene()->GetMainCamera())
			SetMain();
	}
	void CameraComponent::UpdateCameraTransform(const TransformComponent& transform)
	{
		_cam->SetTransform(transform);
	}

	void CameraComponent::SetMain()
	{
		SceneManager::GetCurrentScene()->SetMainCamera(_cam);
	}
}