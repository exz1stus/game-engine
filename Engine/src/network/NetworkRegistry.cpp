#include "engpch.h"
#include "NetworkRegistry.h"
namespace eng
{
	uint32_t NetworkRegistry::_netVarIDs = 0;

	std::unordered_map<uint32_t, inetvar_reciever*> NetworkRegistry::_registry;
	std::stack<uint32_t> NetworkRegistry::_freeVarIDs;
	uint32_t NetworkRegistry::AssignID(inetvar_reciever* reciever)
	{
		uint32_t id;
		if (!_freeVarIDs.empty())
		{
			id = _freeVarIDs.top();
			_freeVarIDs.pop();
		}
		else
		{
			id = _netVarIDs;
			_netVarIDs++;
		}

		_registry[id] = reciever;
		return id;
	}
	void NetworkRegistry::FreeID(uint32_t id)
	{
		_freeVarIDs.push(id);
		_registry[id] = nullptr;
	}
}