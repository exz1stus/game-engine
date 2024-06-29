#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <unordered_map>
#include "NetworkPacket.h"

namespace eng
{
	class inetvar_reciever
	{
	public:
		virtual void on_value_recieved(Packet& packet) = 0;
	};

	class NetworkRegistry
	{
	public:
		static uint32_t AssignID(inetvar_reciever* reciever);
		static void FreeID(uint32_t id);
		//static void RecieveData(uint32_t id, Packet data);
	private:
		static std::unordered_map<uint32_t, inetvar_reciever*> _registry;

		static uint32_t _netVarIDs;
		//static uint32_t _netEventsIDs;

		static std::stack<uint32_t> _freeVarIDs;
		//static std::stack<uint32_t> _freeEventIDs;
	};
}