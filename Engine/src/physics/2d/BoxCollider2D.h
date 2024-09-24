#pragma once
#include "PolygonCollider2D.h"

namespace eng
{
	class BoxCollider2D : public PolygonCollider2D
	{
	public:
		BoxCollider2D(const Rigidbody2D& bodyID, const glm::vec2 size = glm::vec2(1.0f));
		~BoxCollider2D();

		void SetSize(const glm::vec2& size);
	private:
		glm::vec2 _size;
	};
}