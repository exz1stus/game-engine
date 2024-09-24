#include "engpch.h"
#include "Rigidbody2D.h"
#include "glm/trigonometric.hpp"

namespace eng
{
	Rigidbody2D::Rigidbody2D(b2BodyId bodyID)
		: _bodyID(bodyID)
	{}
	Rigidbody2D::~Rigidbody2D()
	{
		//b2DestroyBody(_bodyID);
	}
	glm::vec2 Rigidbody2D::GetPosition() const
	{
		auto pos = b2Body_GetPosition(_bodyID);
		return glm::vec2(pos.x, pos.y);
	}
	float Rigidbody2D::GetRotation() const
	{
		auto rot = b2Body_GetRotation(_bodyID);
		return glm::degrees(b2Rot_GetAngle(rot));;
	}
	void Rigidbody2D::AddForce(const glm::vec2& force)
	{
		b2Body_ApplyForceToCenter(_bodyID, {force.x, force.y}, false);
	}
	void Rigidbody2D::AddTorque(float torque)
	{
		b2Body_ApplyTorque(_bodyID, torque, false);
	}
}