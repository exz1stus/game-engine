#pragma once
#include <enet.h>
#include "network/connections/IConnection.h"

namespace eng
{
	class EnetHost;

	class EnetConnection : public IConnection, public std::enable_shared_from_this<EnetConnection>
	{
	public:
		EnetConnection(EnetHost* owner);
		EnetConnection(ENetPeer* peer);
		void Connect(const std::string& host, uint32_t port);
		void Disconnect() override;
		void Send(Packet packet) override;
		bool IsConnected() const override { return _peer != nullptr; }

		bool operator==(const IConnection& other) override;
	private:
		ENetPeer* _peer;
		//ENetHost* _owner;
		EnetHost* _owner;
	};
}