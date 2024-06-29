#pragma once
#include <string>
#include "network/NetworkPacket.h"
namespace eng
{
	class IConnection
	{
	public:
		virtual void Connect(const std::string& host, uint32_t port) = 0;
		virtual void Disconnect() = 0;
		virtual void Send(Packet packet) = 0;
		virtual bool IsConnected() const = 0;

		virtual bool operator==(const IConnection& other) = 0;
	};
}