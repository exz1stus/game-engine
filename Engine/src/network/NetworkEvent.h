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
		using EventListener = std::function<void(Args...)>;

		NetworkEvent()
		{
			eventID = NetworkRegistry<inetevent_reciever>::AssignID(this);
		}
		NetworkEvent(const EventListener& listener)
			:Event<Args...>(listener)
		{
		}

		~NetworkEvent()
		{
			NetworkRegistry<inetevent_reciever>::FreeID(eventID);
		}

		void Invoke(Args... args) override
		{
			InvokeParams((int)NetworkMessages::EventClientRPC, args...);
		}

		void InvokeParams(int type, Args... args)
		{
			NetworkMessage msg(GetInvokePacket(type, args...));
			NetworkManager::AddNetworkEvent(msg);
			InvokeLocally(args...);
		}

		void InvokeParams(NetworkMessage& msg, int type, Args... args)
		{
			msg._data = GetInvokePacket(type, args...);
			NetworkManager::AddNetworkEvent(msg);
			InvokeLocally(args...);
		}

		void InvokeLocally(Args... args)
		{
			Event<Args...>::Invoke(args...);
		}

		Packet GetInvokePacket(int type, Args... args)
		{
			Packet packet;
			packet.header.id = type;
			packet << eventID;

			ClientRpcHeader header;
			header.senderID = NetworkManager::GetHostID();

			packet << header;

			(packet << ... << args);
			return packet;
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