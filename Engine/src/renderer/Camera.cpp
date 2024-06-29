#include "engpch.h"
#include "Camera.h" 
#include "renderer/RenderingEvents.h"
#include "ecs/CoreComponents.h"
#include "misc/Utilities.h"
#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	Camera::Camera(float left, float right, float bottom, float top, CameraProjection projection)
		:_projMode(projection), _view(1.0f), _projection(1.0f)
	{
		SetPosition(_position);
		SetProjection(left, right, bottom, top);
		RenderingEvents::OnWindowResized.Bind(&Camera::ResizeProjection, this);
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		if (_projMode == CameraProjection::ORTHOGRAPHIC)
		{
			_projection = glm::ortho(left, right, bottom, top, -1.0f, 100.0f);
			//float zoomFactor = 1.0f;
			//_projection = glm::scale(_projection, glm::vec3(zoomFactor, zoomFactor, zoomFactor));
		}
		else
		{
			if (top == 0) return;
			float aspectRatio = right / top;
			_projection = glm::perspective(glm::radians(_fov), aspectRatio, 0.1f, 1000.0f);
		}
	}
	void Camera::ResizeProjection(const uint16_t width, const uint16_t height)
	{
		SetProjection(-width / 2, width / 2, -height / 2, height / 2);
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		_position = position;
		RecalculateViewMatrix();
	}
	void Camera::SetTransform(const TransformComponent& transform)
	{
		_position = transform.position;
		_rotation = transform.rotation;

		_front = transform.GetForward();
		_up = transform.GetUp();

		RecalculateViewMatrix();
	}
	void Camera::RecalculateViewMatrix()
	{
		_view = glm::lookAt(_position, _position + _front, _up);
	}
}
