#pragma once
#include "misc/reactive_ptr.h"
#include "NetworkManager.h"
#include "NetworkRegistry.h"
#include <iostream>

namespace eng
{
	template<typename T>
	class netvar : public reactive_ptr<T>, inetvar_reciever
	{
	public:
		netvar()
		{
			id = NetworkRegistry::AssignID((inetvar_reciever*)this);
			std::cout<<"Assigning " <<id<<"\n";
		}
		~netvar()
		{
			NetworkRegistry::FreeID(id);
		}

		void on_value_recieved(Packet& p) override
		{
			T data;
			p >> data;

			//set(data);
		}
	private:
		uint32_t id;

		void on_modified() override
		{
			Packet p;
			//p << get();

			//NetworkManager::SendToServer();
		}
	};
}