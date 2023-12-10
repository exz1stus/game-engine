#include "engpch.h"
#include "Camera.h"
namespace eng
{
	Camera::Camera(float left, float right, float bottom, float top, bool isOrthographic)
		:isOrthographic(isOrthographic), _view(1.0f), _projection(1.0f)
	{
		SetProjection(left, right, bottom, top);
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		if (isOrthographic)
		{
			_projection = glm::ortho(left, right, bottom, top, -1.0f, 100.0f);

			return;
		}
		else
		{
			_projection = glm::perspective(glm::radians(_fov), (float)right / (float)top, 0.1f, 100.0f);

			return;
		}
	}
}
