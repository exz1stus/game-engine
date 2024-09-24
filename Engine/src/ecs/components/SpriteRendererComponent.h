#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "renderer/platform/opengl/Texture2D.h"
namespace eng
{
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