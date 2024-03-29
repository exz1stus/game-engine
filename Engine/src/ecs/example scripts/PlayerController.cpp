#include "engpch.h"
#include "PlayerController.h"

namespace eng
{
	void PlayerController::OnUpdate()
	{
		auto& transform = GetComponent<TransformComponent>();
		transform.position.x += 0.1f;
	}
}

