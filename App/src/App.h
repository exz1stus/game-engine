#pragma once
#include "EntryPoint.h"
#include "ecs/Entity.h"

class Game : public eng::Application
{
public:
	Game();
private:
	eng::Entity e;
	eng::Entity marker;
	eng::Entity cam;
	void Update();
};