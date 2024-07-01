#pragma once
#include "events/Event.h"
#include "network/NetworkPacket.h"
#include "network/NetworkManager.h"
#include "network/NetworkRegistry.h"
#include <stack>
namespace eng
{
    struct ClientRpcHeader
    {
        size_t senderID;
    };

    class inetevent_reciever
    {
    public:
        virtual void on_recieved(Packet& packet) = 0;
    };

	template<typename... Args>
	class NetworkEvent : public Event<Args...>, inetevent_reciever
	{
    public:
        NetworkEvent()
        {
            eventID = NetworkRegistry<inetevent_reciever>::AssignID(this);
        }

        ~NetworkEvent()
        {
            NetworkRegistry<inetevent_reciever>::FreeID(eventID);
        }

		void Invoke(Args... args) override
		{
			Packet packet;
            packet.header.id = (int)NetworkMessages::EventClientRPC;
			packet << eventID;

            ClientRpcHeader header;
            header.senderID = NetworkManager::GetHostID();

            packet << header;

			(packet << ... << args);

            NetworkManager::AddNetworkEvent(packet);
            InvokeLocally(args...);
		}

        void InvokeLocally(Args... args)
        {
            Event<Args...>::Invoke(args...);
        }
    private:
        size_t eventID;

        template <typename T>
        T Deserialize(eng::Packet& packet)
        {
            T data;
            packet >> data;
            return data;
        }

        void InvokeOnReceive(Packet& packet)
        {    
            InvokeLocally(Deserialize<Args>(packet)...);
        }

        void on_recieved(Packet& packet) override
        {
            InvokeOnReceive(packet);
        }
	};
}