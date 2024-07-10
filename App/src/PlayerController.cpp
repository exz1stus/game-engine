#include "PlayerController.h"
#include "input/Input.h"

void PlayerController::OnInit()
{
	transform = GetComponentReactive<TransformComponent>();

	netPosition.GetOnModified() += [this]() {
		transform->position = netPosition.get();
	};
}

void PlayerController::OnUpdate()
{
	if (!isMine)
		return;

	glm::vec3 movement = glm::vec3(0);

	if (Input::GetKeyDown(KeyCode::KEY_W)) movement.y += 1;
	if (Input::GetKeyDown(KeyCode::KEY_S)) movement.y -= 1;
	if (Input::GetKeyDown(KeyCode::KEY_A)) movement.x -= 1;
	if (Input::GetKeyDown(KeyCode::KEY_D)) movement.x += 1;

	if (movement == glm::vec3(0))
		return;

	movement = glm::normalize(movement) * moveSpeed * (float)GameTime::GetDeltaTime();
	netPosition.getsc() = netPosition.get() + movement;
}