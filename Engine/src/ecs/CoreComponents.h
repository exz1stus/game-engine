#pragma once
#include <functional>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "renderer/platform/opengl/Texture2D.h"
#include "ScriptComponent.h"
namespace eng
{
	struct TransformComponent
	{
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		/*const glm::mat4 GetTransform() const
		{
			glm::mat4 transform = glm::translate(transform, position);// *glm::quat(glm::quat(rotation), )
			return transform;
		}*/
	};

	struct SpriteRendererComponent
	{
		glm::vec3 color = { 1.0f, 1.0f, 1.0f };
		float alpha = 1.0f;
		std::shared_ptr<Texture2D> texture;

		const glm::vec4 GetRGBA() const //& ?
		{
			return glm::vec4(color.x, color.y, color.z, alpha);
		}
	};
}