#include "engpch.h"
#include "SystemManager.h"
#include "systems/ScriptSystem.h"
#include "systems/Rigidbody2DSystem.h"
#include "systems/BoxCollider2DSystem.h"
namespace eng
{
	std::vector<std::unique_ptr<System>> SystemManager::_systems;

	void SystemManager::Init()
	{
		AddSystem<ScriptSystem>();
		AddSystem<Rigidbody2DSystem>();
		AddSystem<BoxCollider2DSystem>();
	}
}
