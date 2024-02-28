#pragma once
#include "renderer/Camera.h"
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
		//static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Texture2D& texture);

		static void BeginScene(/*const Camera& camera*/);
		static void EndScene();
		static void Flush();

	private:
		//batching
		static void StartBatch();
		static void NextBatch();

		static std::unique_ptr<Camera> _cam;
	};
}