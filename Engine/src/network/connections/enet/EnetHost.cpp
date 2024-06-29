#include "engpch.h"
#include "EnetHost.h"
#include "EnetConnection.h"

namespace eng
{
	EnetHost::EnetHost()
		:_host(nullptr)
	{
	}
	EnetHost::~EnetHost()
	{
		enet_host_destroy(_host);
	}
	void EnetHost::Tick()
	{
		ENetEvent event;
		while (enet_host_service(_host, &event, 0) > 0)
		{
			switch (event.type)
			{

			case ENET_EVENT_TYPE_CONNECT:
			{
				std::shared_ptr<IConnection> incomingConn = std::make_shared<EnetConnection>(event.peer);
				OnConnected(incomingConn);
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				std::shared_ptr<IConnection> outgoingConn = std::make_shared<EnetConnection>(event.peer);
				OnDisconnected(outgoingConn);
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE:
			{
				Packet packet = Packet::DeserializePacket(event.packet->data, event.packet->dataLength);
				OnPacketRecieved(packet);
				enet_packet_destroy(event.packet);
				break;
			}

			case ENET_EVENT_TYPE_NONE:
			default:
				break;
			}
		}
	}
	EnetClient::EnetClient()
	{
		_host = enet_host_create(nullptr, 1, 2, 0, 0);
		if (!_host)
			Logger::CriticalError("Failed to create ENet client");
	}
	EnetServer::EnetServer()
	{
		ENetAddress address{};
		address.host = ENET_HOST_ANY;
		address.port = 7777;
		_host = enet_host_create(&address, 32, 2, 0, 0);
		if (!_host)
			Logger::CriticalError("Failed to create ENet server");
	}
}