#pragma once
#include "ecs/CoreComponents.h"
#include "physics/2d/Rigidbody2D.h"

namespace eng
{
	class Scene;

	struct Rb2DComponent
	{
	public:
		void AttachRB(std::shared_ptr<Rigidbody2D> body) { _body = body; }
		glm::vec2 GetPhysPosition() const { return _body->GetPosition(); }
		float GetPhysRotation() const { return _body->GetRotation(); }

		void AddForce(const glm::vec2& force) { _body->AddForce(force); }
		void AddTorque(float torque) { _body->AddTorque(torque); }
	//private:
		std::shared_ptr<Rigidbody2D> _body;
	};
}