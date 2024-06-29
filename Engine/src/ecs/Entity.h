#pragma once
#include "entt/entt.hpp"
#include "SceneManager.h"

namespace eng
{	
	template <typename Component>
	class cmp_ref;

	class Entity
	{
	public:
		Entity()
		{
			id = SceneManager::GetCurrentScene()->AddEntity();
		}
		Entity(const uint32_t id)
		{
			this->id = (entt::entity)id;
		}
		Entity(const entt::entity id)
		{
			this->id = id;
		}
		~Entity() = default;

		template<typename T>
		bool HasComponent() const
		{
			return SceneManager::GetCurrentScene()->_registry.any_of<T>(id);
		}
		template<typename T>
		cmp_ref<T> GetComponentReactive() const
		{
			return cmp_ref(GetComponent<T>(),id);
		}
		template<typename T>
		T& GetComponent() const
		{
			if (!HasComponent<T>())
			{
				Logger::Error("Entity id:{} doesn't have the component", (uint32_t)id);
			}
			return SceneManager::GetCurrentScene()->_registry.get<T>(id);
		}
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				Logger::Error("Entity id:{} already has the component", (uint32_t)id);
				return GetComponent<T>();
			}
			T& component = SceneManager::GetCurrentScene()->_registry.emplace<T>(id, std::forward<Args>(args)...);
			return component;
		}
		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				Logger::Error("Entity id:{} doesn't have the component", (uint32_t)id);
				return;
			}
			SceneManager::GetCurrentScene()->_registry.remove<T>(id);
		}
		bool operator==(const Entity& other) const
		{
			return id == other.id;
		}
		template<typename T>
		void Patch()
		{
			SceneManager::GetCurrentScene()->_registry.patch<T>(id);
		}

		operator const entt::entity() const { return id; }
		operator const uint32_t() const { return (uint32_t)id; }
	private:
		entt::entity id;
		//static Scene _currentScene;
	};
}

