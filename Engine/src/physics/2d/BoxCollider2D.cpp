#include "engpch.h"
#include "BoxCollider2D.h"

namespace eng
{
	BoxCollider2D::BoxCollider2D(const Rigidbody2D& rb, const glm::vec2 size)
		:_size(size)
	{
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		b2Polygon dynamicBox = b2MakeBox(_size.x, _size.y);
		InitPolygon(rb, shapeDef, dynamicBox);

		SetDensity(1.0f);
		SetFriction(0.3f);
	}
	BoxCollider2D::~BoxCollider2D()
	{
		DestroyShape();
	}
	void BoxCollider2D::SetSize(const glm::vec2& size)
	{
		//TODO
	}
}