#include "engpch.h"
#include "ScriptSystem.h"
#include "ecs/components/ScriptComponent.h"
#include "ApplicationEvents.h"
namespace eng
{
	void ScriptSystem::Init()
	{
		ApplicationEvents::OnUpdate.Bind(&ScriptSystem::Update, this);
		GetSceneRegistry().on_destroy<ScriptComponent>().connect<&ScriptSystem::RemoveScriptCallback>(this);
	}
	
	void ScriptSystem::Update()
	{
		auto view = GetSceneRegistry().view<ScriptComponent>();

		for (Entity entity : view)
		{
			auto& script = entity.GetComponent<ScriptComponent>();

			if (!script.instantiated)
			{
				InstantiateScripts(entity, script);
			}

			for (const auto& [type, ptr] : script._scripts)
			{
				ptr->OnUpdate();
			}
		}
	}

	void ScriptSystem::InstantiateScripts(Entity id, ScriptComponent& script)
	{
		while (!script._scriptsToInstantiate.empty())
		{
			InstantiateFunctionPtr& func = script._scriptsToInstantiate.top();
			auto instance = func(&script);
			instance->id = id;
			instance->OnInit();
			script._scriptsToInstantiate.pop();
		}
		script.instantiated = true;
	}

	void ScriptSystem::RemoveScriptCallback(entt::registry& registry, Entity entity)
	{
		entity.GetComponent<ScriptComponent>().DestroyScripts();
	}
}