#pragma once
#include "core/EntryPoint.h"
#include "ecs/Entity.h"

#include "network/Client.h"
#include <memory>

using namespace eng;

class Game : public Application
{
public:
	Game();
private:
	Entity cam;
	Entity e;
	void Start();
	void Update();
	void Render();

	bool started = false;
};