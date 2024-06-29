#pragma once
#include "network/NetworkPacket.h"
#include "connections/enet/EnetHost.h"
#include "connections/enet/EnetConnection.h"

namespace eng
{
	class Client : public EnetClient
	{
	public:
		Client();
		~Client();
		bool Connect(const std::string& host, uint32_t port);
		bool Disconnect();
		//void ServerCommand(Packet& packet);
		std::shared_ptr<IConnection> GetConnection() const { return _connection; }
	private:
		void OnPacketRecieved(Packet& packet) override;
		void OnConnected(std::shared_ptr<IConnection> con) override;
		void OnDisconnected(std::shared_ptr<IConnection> con) override;

		std::shared_ptr<IConnection> _connection;
	};
}


