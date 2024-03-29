#include "engpch.h"
#include "Camera.h" 
#include "renderer/RenderingEvents.h"
#include "misc/Utilities.h"

#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	Camera::Camera(float left, float right, float bottom, float top, bool isOrthographic)
		:isOrthographic(isOrthographic), _view(1.0f), _projection(1.0f)
	{
		SetPosition(_position);
		SetProjection(left, right, bottom, top);
		RenderingEvents::OnWindowResized.Bind(&Camera::ResizeProjection, this);
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		if (isOrthographic)
		{
			_projection = glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
			float zoomFactor = 1.0f;
			_projection = glm::scale(_projection, glm::vec3(zoomFactor, zoomFactor, zoomFactor));
		}
		else
		{
			if (top == 0) return;
			float aspectRatio = right / top;
			_projection = glm::perspective(glm::radians(_fov), aspectRatio, 0.1f, 1000.0f);

		}
	}
	void Camera::ResizeProjection(uint16_t width,uint16_t height)
	{
		SetProjection(-width /2, width /2, -height /2, height /2);
	}
	void Camera::SetRotation(const glm::vec3& rotation)
	{
		_rotation = rotation;
		_direction.x = cos(glm::radians(_rotation.x - 90)) * cos(glm::radians(_rotation.y));
		_direction.y = sin(glm::radians(_rotation.y));
		_direction.z = sin(glm::radians(_rotation.x - 90)) * cos(glm::radians(_rotation.y));
		_direction = glm::normalize(_direction);

		RecalculateViewMatrix();
	}
	void Camera::SetPosition(const glm::vec3& position)
	{
		_position = position;
		RecalculateViewMatrix();
	}
	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position);

		glm::mat4 rot = glm::lookAt(_position, _position + _direction, _up)*
						glm::rotate(glm::mat4(transform), glm::radians(_rotation.z), _direction);
			

		_view = rot * glm::inverse(transform);

	}
}
