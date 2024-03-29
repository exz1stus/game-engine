#pragma once
#include "ecs/Entity.h"
#include "BehaviourScript.h"
#include <type_traits>
#include "debug/logger/Logger.h"
namespace eng
{
	struct ScriptComponent
	{
	public:
		template<typename T>
		void AddScript()
		{
			if (!std::is_base_of<BehaviourScript, T>::value)
			{
				Logger::Error("Script must be derived from BehaviourScript");
			}

			InstantiateFunction = []() { return static_cast<BehaviourScript*>(new T); };
			DestroyFunction = [](BehaviourScript* instance) {
				delete (T*)instance;
				instance = nullptr;
				};
		}

		void Destroy()
		{
			if (!_scriptInstance)
			{
				Logger::Error("Can't delete script component, because instance doesn't exist EntityId: " + 
					(uint32_t)_scriptInstance->GetAttachedEntity());
				return;
			}
			_scriptInstance->OnDestroy();
			DestroyFunction(_scriptInstance);
		}

	private:
		BehaviourScript* (*InstantiateFunction)();
		void (*DestroyFunction)(BehaviourScript* instance);

		BehaviourScript* _scriptInstance;		
		friend class Scene;
	};
}