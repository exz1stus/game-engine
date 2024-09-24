#pragma once
#include "System.h"
namespace eng
{
	class SystemManager
	{
	public:
		static void Init();
		template<typename T>
		static void AddSystem()
		{
			auto system = std::make_unique<T>();
			system->Init();
			_systems.push_back(std::move(system));
		}
	private:
		static std::vector<std::unique_ptr<System>> _systems;
	};
}