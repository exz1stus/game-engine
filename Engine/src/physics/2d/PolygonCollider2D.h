#pragma once
#include "Collider2D.h"
namespace eng
{
	class PolygonCollider2D : public Collider2D
	{
	public:
		void InitPolygon(const Rigidbody2D& rb, const b2ShapeDef& shapeDef, const b2Polygon& polygon);
	};
}

