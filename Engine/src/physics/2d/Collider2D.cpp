#include "engpch.h"
#include "Collider2D.h"

namespace eng
{
	void Collider2D::DestroyShape()
	{
		b2DestroyShape(_shapeID);
	}
}