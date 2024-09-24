#pragma once
#include "physics/2d/BoxCollider2D.h"

namespace eng
{
	struct BoxCollider2DComponent
	{
	public:
		std::unique_ptr<BoxCollider2D> _collider;
	};
}