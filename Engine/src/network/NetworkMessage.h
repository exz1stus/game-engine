#pragma once
#include "NetworkPacket.h"
#include "events/Event.h"
namespace eng
{
	/*template<typename T>
	class NetworkEvent;*/

	class NetworkMessage
	{
	public:
		NetworkMessage(){}
		NetworkMessage(Packet data)
			:_data(data)
		{ }

		virtual Packet& GetData() { return _data; }
		operator Packet() { return GetData(); }
		Packet _data;
	private:

		/*template <typename U>
		friend class NetworkEvent;*/
	};
}