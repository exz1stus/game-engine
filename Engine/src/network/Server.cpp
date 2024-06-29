#include "engpch.h"
#include "Server.h"

namespace eng
{
	void Server::Broadcast(Packet& packet)
	{
		for (auto& con : _connections)
		{
			con->Send(packet);
		}
	}
	void Server::OnPacketRecieved(Packet& packet)
	{
		int x = 0;
		Broadcast(packet);
		packet >> x;
		Logger::Log("Recieved a packet of size {}, data {}", packet.header.size, x);

	}
	void Server::OnConnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("New client has connected");
		_connections.push_back(con);
	}
	void Server::OnDisconnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("Client has diconnected");

		//_connections.erase(std::remove_if(_connections.begin(), _connections.end(),
		//	[con](const std::shared_ptr<IConnection>& other)s {
		//		return con == other;
		//	}));
		//TODO : rewrite
	}
}