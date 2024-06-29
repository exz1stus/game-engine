#pragma once
#include "EntryPoint.h"
#include "ecs/Entity.h"

#include "network/Client.h"
#include <memory>

using namespace eng;

class Game : public eng::Application
{
public:
	Game();
private:
	std::unique_ptr<Client> client;
	eng::Entity cam;

	void Update();
};