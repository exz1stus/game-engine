#include "engpch.h"
#include "Client.h"
namespace eng
{
	Client::Client()
	{
		_connection = std::make_shared<EnetConnection>(_host);
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
		Logger::Log("Client : Recieved a packet of size {}", packet.header.size);
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

