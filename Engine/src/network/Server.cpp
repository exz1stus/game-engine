#include "engpch.h"
#include "Server.h"

#include "NetworkManager.h"

namespace eng
{
	static size_t idCounter = 1;

	void Server::Broadcast(Packet& packet)
	{
		for (auto& con : _connections)
		{
			con.second->Send(packet);
		}
	}
	void Server::ClientRpc(Packet& packet, ClientRpcHeader header, size_t localClient)
	{
		size_t sender = header.senderID;

		for (auto& con : _connections)
		{
			if(con.first != sender && con.first != localClient)
				con.second->Send(packet);
		}
	}
	void Server::OnPacketRecieved(Packet& packet)
	{
		NetworkManager::OnRecieved(packet);

	}
	void Server::OnConnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("New client has connected");
		_connections[idCounter] = con;

		Packet p;
		p.header.id = (int)NetworkMessages::AssignIDToClient;
		p << idCounter;

		con->Send(p);

		idCounter++;
	}
	void Server::OnDisconnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("Client has diconnected");

		//TODO : _connections.erase()
	}
}