#pragma once
#include "network/NetworkPacket.h"
#include "connections/enet/EnetHost.h"
#include "connections/enet/EnetConnection.h"
#include "NetworkEvent.h"

namespace eng
{
	class Server : public EnetServer
	{
	public:
		void Broadcast(Packet& packet);
		void ClientRpc(Packet& packet, ClientRpcHeader header, size_t localClient = 0);
	private:
		void OnConnected(std::shared_ptr<IConnection> con) override;
		void OnDisconnected(std::shared_ptr<IConnection> con) override;
		void OnPacketRecieved(Packet& packet) override;

		std::unordered_map<size_t, std::shared_ptr<IConnection>> _connections;
	};
}

