#pragma once
#include <glm/glm.hpp>
#include "events/Event.h"

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


		void ResizeProjection(uint16_t width, uint16_t height);

		const glm::vec3 GetPosition() const { return _position; }

		void SetRotation(const glm::vec3& rotation);
		void SetPosition(const glm::vec3& position);
		
	private:
		void RecalculateViewMatrix();
		//void RecalculateProjectionMatrix();


		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };

		glm::vec3 _direction = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _up = { 0.0f, 1.0f, 0.0f };

		float _fov = 75.0f;

		bool isOrthographic = true;   

	};
}

