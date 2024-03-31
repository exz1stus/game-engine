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
				Logger::Error("Script must be derived from BehaviourScript, EntityId:" +
					(uint32_t)_scriptInstance->GetAttachedEntity());
				return;
			}

			InstantiateFunction = []() { return static_cast<BehaviourScript*>(new T); };
			DestroyFunction = [](BehaviourScript* instance) {
				delete (T*)instance;
				instance = nullptr;
			};
		}

		void RemoveScript()
		{
			if (!_scriptInstance)
			{
				Logger::Error("Can't remove script component, because instance doesn't exist");
				return;
			}
			_scriptInstance->OnDestroy();
			DestroyFunction(_scriptInstance);
		}

	private:
		BehaviourScript* (*InstantiateFunction)();
		void (*DestroyFunction)(BehaviourScript* instance);

		BehaviourScript* _scriptInstance = nullptr;		
		friend class Scene;

	};
}