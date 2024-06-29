#include "engpch.h"
#include "EnetConnection.h"
namespace eng
{
	EnetConnection::EnetConnection(ENetHost* owner)
		:_peer(nullptr), _owner(owner)
	{}

	EnetConnection::EnetConnection(ENetPeer* peer)
		:_peer(peer), _owner(nullptr)
	{
		Logger::Log("peer based conn construction !!!");
	}

	void EnetConnection::Connect(const std::string& host, uint32_t port)
	{
		if (IsConnected())
		{
			Logger::Error("Trying to connect in already established connection");
			return;
		}  

		ENetAddress address { 0 }; //typyj kusok zalupy blyad zajniaw w mene 10 jebanych godyn debuggowania c++ typa hujnia dla konczenych pidarasiw 9/
		enet_address_set_host(&address, host.c_str());
		address.port = port;

		_peer = enet_host_connect(_owner, &address, 2, 0);

		Logger::Assert(_peer != nullptr,"");

		if (!IsConnected())
			Logger::Error("Failed to connect to host");

		//////////////////////////////////////////
		ENetEvent event;

		if (enet_host_service(_owner, &event, 3000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT)
		{
			Logger::Log("Connection succeeded.");
			//_owner->OnConnected(std::make_shared<IConnection>(this));
		}
		else
		{
			enet_peer_reset(_peer);
			_peer = nullptr;
			Logger::Error("Connection failed");
			//_owner->OnDisconnected(std::make_shared<IConnection>(this));
		}
	}
	void EnetConnection::Disconnect()
	{
		enet_peer_disconnect_now(_peer, 0);
		//_owner->OnDisconnected(std::make_shared<IConnection>(this));
		_peer = nullptr;
	}
	void EnetConnection::Send(Packet packet)
	{
		if (!IsConnected())
		{
			Logger::Error("Not connected : can't send a packet");
			return;
		}

		ENetPacket* enetPacket = enet_packet_create(nullptr, packet.size(), ENET_PACKET_FLAG_RELIABLE);

		std::memcpy(enetPacket->data, &packet.header, sizeof(packet.header));
		std::memcpy(enetPacket->data + sizeof(packet.header), packet.body.data(), packet.body.size());

		if (enetPacket == nullptr)
		{
			Logger::Error("Failed to create ENet packet");
			return;
		}

		enet_peer_send(_peer, 0, enetPacket);
		//enet_host_flush(_peer->host);
		//enet_packet_destroy(enetPacket);
	}

	// Equality operator for in6_addr (IPv6 addresses)
	bool operator==(const in6_addr& lhs, const in6_addr& rhs)
	{
		return std::memcmp(&lhs, &rhs, sizeof(in6_addr)) == 0;
	}

	// Equality operator for ENetAddress
	bool operator==(const ENetAddress& lhs, const ENetAddress& rhs)
	{
		if (lhs.port != rhs.port)
		{
			return false;
		}
		// Handle IPv4 addresses
		if (lhs.host == rhs.host)
		{
			return true;
		}
		// Handle IPv6 addresses
		const in6_addr* lhs_in6 = reinterpret_cast<const in6_addr*>(&lhs.host);
		const in6_addr* rhs_in6 = reinterpret_cast<const in6_addr*>(&rhs.host);
		return *lhs_in6 == *rhs_in6;
	}

	bool EnetConnection::operator==(const IConnection& other)
	{
		const EnetConnection* otherConn = dynamic_cast<const EnetConnection*>(&other);
		if (!otherConn)
		{
			Logger::Error("Comparable connection is another type of connection");
			return false;
		}

		return this->_peer->address == otherConn->_peer->address;
	}
}