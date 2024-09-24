#pragma once
#include "box2d/box2d.h"
#include "physics/PhysWorldProperties.h"
#include "Rigidbody2D.h"

namespace eng
{
	class PhysWorld
	{
	public:
		PhysWorld(const PhysWorldProperties& properties);
		~PhysWorld();
		void PhysTick();
		std::shared_ptr<Rigidbody2D> CreateBody(const glm::vec2& targetPosition, float targetRotationZ);
	private:
		b2WorldId _world;

		float _physStep = 1 / 144.0f;
		int _subStepCount = 4;
	};
}