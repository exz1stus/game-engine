#pragma once
#include "events/Event.h"
#include "network/NetworkPacket.h"
#include "network/NetworkManager.h"
#include "network/NetworkRegistry.h"
namespace eng
{
	template<typename... Args>
	class NetworkEvent : public Event<Args>
	{
    public:
		void Invoke(Args... args) override
		{
			//uint32_t eventID = NetworkRegistry::AssignEventID();

			Packet packet;
			packet << eventID;
			(packet << ... << args);

            //send
            //NetworkManager::ClientRpc()

            InvokeLocally(args...)
		}

        /*void operator()(Args... args) override
        {
            Invoke();
        }*/


        void InvokeLocally(Args... args)
        {
            Event<Args>::Invoke(args...);
        }

        void InvokeOnReceive(Packet& packet)
        {
            InvokeLocally(args...);
        }

	};
}