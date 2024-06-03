#pragma once
#include "EntryPoint.h"
#include "ecs/Entity.h"

class Game : public eng::Application
{
public:
	Game();
private:
	eng::Entity e;
	eng::Entity cam;

	eng::Entity rotX;
	eng::Entity rotY;
	eng::Entity rotZ;
	void Update();
};