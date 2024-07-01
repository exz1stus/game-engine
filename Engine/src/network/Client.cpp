#include "engpch.h"
#include "Client.h"
#include "NetworkManager.h"
namespace eng
{
	Client::Client()
	{
		_connection = std::make_shared<EnetConnection>((EnetHost*)this);
	}
	Client::~Client()
	{
		if (_connection->IsConnected())
			Disconnect();
	}

	bool Client::Connect(const std::string& host, uint32_t port)
	{
		_connection->Connect(host, port);
		return _connection->IsConnected();
	}
	bool Client::Disconnect()
	{
		_connection->Disconnect();
		return !_connection->IsConnected();
	}

	void Client::OnPacketRecieved(Packet& packet)
	{
		if (packet.header.id == (int)NetworkMessages::AssignIDToClient)
		{
			size_t id;
			packet >> id;
			AssignHostID(id);

			Logger::Log("Client assigned id {}", id);

			return;
		}

		Logger::Log("Client : Recieved a packet of size {}", packet.header.size);
		NetworkManager::OnRecieved(packet);
	}

	void Client::OnConnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("Client : connected");
	}

	void Client::OnDisconnected(std::shared_ptr<IConnection> con)
	{
		Logger::Log("Client : disconnected");
	}

}

