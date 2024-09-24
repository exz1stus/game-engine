#pragma once
#include "NetworkPacket.h"
namespace eng
{
	class NetworkMessage
	{
	public:
		NetworkMessage() = default;
		NetworkMessage(Packet data)
			:_data(std::move(data))
		{ }
		virtual ~NetworkMessage() = default;

		virtual Packet& GetData() { return _data; }
		operator Packet() { return GetData(); }
		Packet _data;
	};
}