#include "network/NetworkPacket.h"
#include "connections/IConnection.h"
namespace eng
{
	class IHost
	{
	public:
		virtual void Tick() = 0;
		virtual bool IsCreated() const = 0;
		friend IConnection;
	protected:
		virtual void OnConnected(std::shared_ptr<IConnection> con) = 0;
		virtual void OnDisconnected(std::shared_ptr<IConnection> con) = 0;
		virtual void OnPacketRecieved(Packet& packet) = 0;
	};
}