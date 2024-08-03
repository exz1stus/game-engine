#pragma once
#include "eng.h"
#include "network/netvar.h"
#include "network/components/NetTransformComponent.h"
#include "ecs/component_ref.h"

using namespace eng;

class PlayerController : public BehaviourScript
{
public:
	void OnInit() override;
	void OnUpdate() override;

	bool isMine = false;
private:
	NetTransform transform;

	float moveSpeed = 500.0f;
};

