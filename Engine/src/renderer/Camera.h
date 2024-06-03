#pragma once
#include <glm/glm.hpp>
#include "ecs/CoreComponents.h"

namespace eng
{
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top, bool isOrthographic);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::mat4& GetProjectionMatrix() const { return _projection; }
		const glm::mat4& GetViewMatrix() const { return _view; }
		const glm::mat4& GetViewProjectionMatrix() const { return _projection * _view; }

		void ResizeProjection(const uint16_t width,const uint16_t height);

		void SetPosition(const glm::vec3& position);
		void SetTransform(const TransformComponent& transform);
	private:
		void RecalculateViewMatrix();

		glm::mat4 _view;
		glm::mat4 _projection;

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };

		glm::vec3 _front = { 0.0f, 0.0f, -1.0f };
		glm::vec3 _up = { 0.0f, 1.0f, 0.0f };

		glm::vec3 _worldUp = { 0.0f, 1.0f, 0.0f };

		float _fov = 60.0f;

		bool isOrthographic = true;   

	};
}

