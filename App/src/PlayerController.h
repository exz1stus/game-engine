#pragma once
#include "eng.h"
#include "network/netvar.h"
#include "ecs/component_ref.h"

using namespace eng;

class PlayerController : public BehaviourScript
{
public:
	void OnInit() override;
	void OnUpdate() override;

	ls_netvar<glm::vec3> netPosition;
	bool isMine = false;

private:
	cmp_ref<TransformComponent> transform;

	float moveSpeed = 700.0f;
};

