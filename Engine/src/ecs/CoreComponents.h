#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "renderer/platform/opengl/Texture2D.h"
#include "ScriptComponent.h"
namespace eng
{
	struct TransformComponent
	{
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		
		const glm::vec3 GetUp() const
		{
			return glm::vec3(GetRotationMat4() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		}
		const glm::vec3 GetForward() const
		{
			return glm::vec3(GetRotationMat4() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
		}
		const glm::vec3 GetRight() const
		{
			return glm::vec3(GetRotationMat4() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		}
		const glm::mat4 GetRotationMat4() const
		{
			return glm::toMat4(glm::quat(glm::radians(rotation)));
		}

		const glm::mat4 GetScaleMat4() const
		{
			return glm::scale(glm::mat4(1.0f), scale);
		}
		// TODO : return temporary values
		const glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), position) * GetRotationMat4() * GetScaleMat4();
		}
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