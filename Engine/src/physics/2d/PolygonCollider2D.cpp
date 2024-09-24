#include "engpch.h"
#include "PolygonCollider2D.h"

namespace eng
{
	void PolygonCollider2D::InitPolygon(const Rigidbody2D& rb, const b2ShapeDef& shapeDef, const b2Polygon& polygon)
	{
		_shapeID = b2CreatePolygonShape(rb._bodyID, &shapeDef, &polygon);
	}
}
