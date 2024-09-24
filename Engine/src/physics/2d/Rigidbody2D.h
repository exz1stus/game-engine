#pragma once
#include "box2d/box2d.h"
#include "glm/vec2.hpp"
namespace eng
{
	class Collider2D;
	class PolygonCollider2D;

	class Rigidbody2D
	{
	public:
		Rigidbody2D(b2BodyId bodyID);
		~Rigidbody2D();

		glm::vec2 GetPosition() const;
		float GetRotation() const;
		void AddForce(const glm::vec2& force);
		void AddTorque(float torque);
	private:
		b2BodyId _bodyID;
		friend Collider2D;
		friend PolygonCollider2D;
	};
}