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
		//size_t GetHostID() const { return _hostID; }
		size_t _hostID = 0;
	protected:
		virtual void OnConnected(std::shared_ptr<IConnection> con) = 0;
		virtual void OnDisconnected(std::shared_ptr<IConnection> con) = 0;
		virtual void OnPacketRecieved(Packet& packet) = 0;

		void AssignHostID(size_t id) { _hostID = id; }
	};
}