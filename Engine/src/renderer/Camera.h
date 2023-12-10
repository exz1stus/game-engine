#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	private:
		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		float _rotation = 0.0f;
		float _fov = 45.0f;

		bool isOrthographic = true;   
	};
}

