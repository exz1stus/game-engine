#include "engpch.h"
#include <GLFW/glfw3.h>
#include "renderer/Camera.h"
#include "GameTime.h"



void asd()
{
	glm::vec2 movement = glm::vec2(0);

	float speed = 500.0f;

	auto wind = glfwGetCurrentContext();

	if (glfwGetKey(wind,GLFW_KEY_W))	movement.y = -1;
	if (glfwGetKey(wind,GLFW_KEY_S))	movement.y = 1;
	if (glfwGetKey(wind,GLFW_KEY_A))	movement.x = 1;
	if (glfwGetKey(wind,GLFW_KEY_D))	movement.x = -1;

	if (movement.x != 0 && movement.y != 0) movement = glm::normalize(movement);

	//transform.position.x += -movement.x * speed * GameTime::getDeltaTime();
	//transform.position.y += -movement.y * speed * GameTime::getDeltaTime();
}