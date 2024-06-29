#pragma once
#include "network/NetworkPacket.h"
#include "connections/enet/EnetHost.h"
#include "connections/enet/EnetConnection.h"

namespace eng
{
	class Server : public EnetServer
	{
	public:
		void Broadcast(Packet& packet);
	private:
		void OnConnected(std::shared_ptr<IConnection> con) override;
		void OnDisconnected(std::shared_ptr<IConnection> con) override;
		void OnPacketRecieved(Packet& packet) override;

		std::vector<std::shared_ptr<IConnection>> _connections;
	};
}

