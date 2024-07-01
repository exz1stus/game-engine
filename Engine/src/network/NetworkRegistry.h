#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <unordered_map>
#include "NetworkPacket.h"

namespace eng
{
	template <typename T>
	class NetworkRegistry
	{
	public:
		static size_t AssignID(T* obj)
		{
			Logger::Assert(obj != nullptr, "Object is nullptr");

			size_t id;
			if (!_freeIDs.empty())
			{
				id = _freeIDs.top();
				_freeIDs.pop();
			}
			else
			{
				id = _IDs;
				_IDs++;
			}

			_registry[id] = obj;

			return id;
		}
		static void FreeID(size_t id)
		{
			_freeIDs.push(id);
			_registry[id] = nullptr;
		}
		static T* GetByID(size_t id) 
		{
			if(_registry.contains(id))
				return _registry.at(id); 

			Logger::Error("registry doesn't have the id {}", id);
		}
	private:
		static std::unordered_map<size_t, T*> _registry;

		static size_t _IDs;

		static std::stack<size_t> _freeIDs;
	};

	template <typename T>
	size_t NetworkRegistry<T>::_IDs = 0;

	template <typename T>
	std::unordered_map<size_t, T*> NetworkRegistry<T>::_registry;

	template <typename T>
	std::stack<size_t> NetworkRegistry<T>::_freeIDs;

}