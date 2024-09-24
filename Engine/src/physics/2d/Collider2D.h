#pragma once
#include "Rigidbody2D.h"
namespace eng
{
	class Collider2D
	{
	public:
		float GetFriction() const { return b2Shape_GetFriction(_shapeID); }
		void SetFriction(float friction) { return b2Shape_SetFriction(_shapeID, friction); }

		float GetDensity() const { return b2Shape_GetDensity(_shapeID); }
		void SetDensity(float density) { return b2Shape_SetDensity(_shapeID, density); }

		bool IsTrigger() const { return b2Shape_IsSensor(_shapeID); }
	protected:
		void DestroyShape();

		b2ShapeId _shapeID;
	};
}