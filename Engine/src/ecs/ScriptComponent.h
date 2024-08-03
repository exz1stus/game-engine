#pragma once
#include <type_traits>
#include <typeindex>
#include <stack>
#include <memory>
#include <unordered_map>

#include "ecs/Entity.h"
#include "BehaviourScript.h"
#include "debug/logger/Logger.h"
#include "events/Event.h"
namespace eng
{
	/*struct ScriptComponent
	{
	public:
		template<typename T>
		void AddScript()
		{
			Logger::Assert(std::is_base_of<BehaviourScript, T>::value, "Script must be derived from BehaviourScript, EntityId:{}",
				(uint32_t)_scriptInstance->GetAttachedEntity());

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

		template <typename T>
		T& GetScript()
		{
			Logger::Assert(_scriptInstance, "Script instance is nullptr");

			return *dynamic_cast<T*>(_scriptInstance);
		}

	private:
		BehaviourScript* (*InstantiateFunction)();
		void (*DestroyFunction)(BehaviourScript* instance);

		BehaviourScript* _scriptInstance = nullptr;
		friend class Scene;

	};*/
	struct ScriptComponent;

	using InstantiateFunctionPtr = BehaviourScript* (*)(ScriptComponent*);

	struct ScriptComponent
	{
	public:
		template<typename T>
		void AddScript()
		{
			Logger::Assert(std::is_base_of<BehaviourScript, T>::value,
				"Script must be derived from BehaviourScript");

			if (_scripts.contains(typeid(T)))
			{
				Logger::Warning("Script of this type already exists. Skipping AddScript.");
				return;
			}

			_scriptsToInstantiate.emplace([](ScriptComponent* script) -> BehaviourScript*{
				auto result = script->_scripts.emplace(typeid(T), new T);
				return result.first->second;
				});

			OnDestroy += [](ScriptComponent* script) {
				auto it = script->_scripts.find(typeid(T));
				if (it != script->_scripts.end())
				{
					it->second->OnDestroy();
					delete (T*)it->second;
					script->_scripts.erase(it);
				}
				};

			instantiated = false;
		}

		template<typename T>
		void RemoveScript()
		{
			std::type_index index = typeid(T);

			if (!_scripts.contains(index))
			{
				Logger::Error("Can't remove script component, because instance doesn't exist");
				return;
			}

			_scripts[index]->OnDestroy();
			_scripts.erase(index);
		}

		void DestroyScripts()
		{
			for (auto& [type, ptr] : _scripts)
			{
				ptr->OnDestroy();
			}
			OnDestroy(this);
		}

		template <typename T>
		T& GetScript()
		{
			Logger::Assert(_scripts.contains(typeid(T)), "Script instance is nullptr");

			return *dynamic_cast<T*>(_scripts[typeid(T)]);
		}

	private:
		std::unordered_map<std::type_index, BehaviourScript*> _scripts;
		std::stack<InstantiateFunctionPtr> _scriptsToInstantiate;
		Event<ScriptComponent*> OnDestroy;
		bool instantiated = false;

		friend class Scene;
	};
}