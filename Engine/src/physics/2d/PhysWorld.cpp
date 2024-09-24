#include "engpch.h"
#include "PhysWorld.h"
namespace eng
{
	PhysWorld::PhysWorld(const PhysWorldProperties& properties)
	{
		auto worldDef = b2DefaultWorldDef();
		worldDef.gravity = { properties.g.x, properties.g.y };
		_world = b2CreateWorld(&worldDef);
	}
	PhysWorld::~PhysWorld()
	{
		b2DestroyWorld(_world);
	}
	void PhysWorld::PhysTick()
	{
		b2World_Step(_world, _physStep, _subStepCount);
	}
	std::shared_ptr<Rigidbody2D> PhysWorld::CreateBody(const glm::vec2& targetPosition, float targetRotationZ)
	{
		auto bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = { targetPosition.x, targetPosition.y };
		bodyDef.rotation = b2MakeRot(targetRotationZ);
		bodyDef.gravityScale = 1.0f;
		bodyDef.isAwake = true;
		return std::make_shared<Rigidbody2D>(b2CreateBody(_world, &bodyDef));
	}
}