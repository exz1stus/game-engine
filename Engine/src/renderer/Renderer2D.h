#pragma once
#include "renderer/Camera.h"
#include "renderer/platform/opengl/Texture2D.h"	
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace eng
{
	class Renderer2D
	{
	public:
		static void Init();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture);
		static void DrawQuad(const glm::mat4 transform, const glm::vec4& color, const std::shared_ptr<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture);

		static void BeginScene(/*const Camera& camera*/);
		static void EndScene();
		static void Flush();

		static std::unique_ptr<Camera> _cam;
	private:
		static void StartBatch();
		static void NextBatch();

	};
}