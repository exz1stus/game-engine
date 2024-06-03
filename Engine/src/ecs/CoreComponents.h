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
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		glm::vec3 GetUp() const
		{
			return glm::vec3(GetRotation() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		}

		glm::vec3 GetForward() const
		{
			return glm::vec3(GetRotation() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
		}

		glm::vec3 GetRight() const
		{
			return glm::vec3(GetRotation() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
		}

		glm::quat GetRotation() const
		{
			return glm::quat(glm::radians(rotation));
			glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0, 1.0f, 0));
			glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0, 0));
			glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0, 0, -1.0f));
			//return glm::normalize(qYaw * qRoll * qPitch);
			return glm::normalize(qYaw * qPitch * qRoll);
		}

		glm::mat4 GetRotationMat4() const
		{
			return glm::toMat4(GetRotation());
		}

		glm::mat4 GetScaleMat4() const
		{
			return glm::scale(glm::mat4(1.0f), scale);
		}

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), position) * GetRotationMat4() * GetScaleMat4();
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec3 color = { 1.0f, 1.0f, 1.0f };
		float alpha = 1.0f;
		std::shared_ptr<Texture2D> texture;

		glm::vec4 GetRGBA() const
		{
			return glm::vec4(color.x, color.y, color.z, alpha);
		}
	};
}