#include "engpch.h"
#include "Camera.h" 
#include "renderer/platform/RenderingEvents.h"
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
			_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			return;
		}
		else
		{
			//_projection = glm::perspective(glm::radians(_fov), right / top, -1.0f, 100.0f);
			float aspectRatio = right / top;
			_projection = glm::perspective(glm::radians(_fov), aspectRatio, 0.1f, 10.0f);
			return;
		}
	}
	void Camera::ResizeProjection(uint16_t width,uint16_t height)
	{
		SetProjection(-width /2, width /2, -height /2, height /2);
	}
	void Camera::SetRotation(const glm::vec3& rotation)
	{
		_rotation = rotation;
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

		/*transform = glm::rotate(transform, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));*/

		glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), -glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), -glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), -glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));


		_view = rotateX * rotateY * rotateZ * glm::inverse(transform);

		//_view = glm::lookAt(_position, _position + _direction, _up);
	}
}
