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

	bool Client::Connect(const std::string& host, uint32_t port) const
	{
		_connection->Connect(host, port);
		return _connection->IsConnected();
	}
	bool Client::Disconnect() const
	{
		_connection->Disconnect();
		return !_connection->IsConnected();
	}

	void Client::OnPacketReceived(Packet& packet)
	{
		if (packet.header.id == (int)NetworkMessages::AssignIDToClient)
		{
			size_t id;
			packet >> id;
			AssignHostID(id);

			Logger::Log("Client assigned id {}", id);

			return;
		}

		//Logger::Log("Client : Received a packet of size {}", packet.header.size);
		NetworkManager::OnReceived(packet);
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

