#include "PlayerController.h"
#include "input/Input.h"

void PlayerController::OnInit()
{
	transform = GetComponent<ScriptComponent>().GetScript<NetTransform>();
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

	movement = moveSpeed * (float)GameTime::GetDeltaTime() * glm::normalize(movement);
	*transform.position = transform.position.get() + movement;
}