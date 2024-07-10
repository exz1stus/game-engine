#pragma once
#include "misc/reactive_ptr.h"
#include "NetworkManager.h"
#include "NetworkRegistry.h"
#include "NetworkEvent.h"
#include "NetworkMessage.h"
#include <iostream>

namespace eng
{
	template<typename T>
	class netvar : public reactive_ptr<T>
	{
	public:
		netvar()
		{
			NetOnModified.Bind(&netvar<T>::on_recieved, this);
		}

		void on_recieved(const T data)
		{
			if (isInvoker)
			{
				isInvoker = false;
				return;
			}
			reactive_ptr<T>::set(data);
		}
	protected:
		NetworkEvent<T> NetOnModified;

		bool isInvoker = false; // EEW WWQ QWE

		void on_modified() override
		{
			isInvoker = true;
			NetOnModified.InvokeParams((int)NetworkMessages::EventNetvarUpdated, reactive_ptr<T>::get());
		}
	};

	template<typename T>
	class ls_netvar;

	template<typename T>
	class ls_netvar_msg : public NetworkMessage
	{
	public:
		ls_netvar_msg(ls_netvar<T>& var)
			: _var(var)
		{}

		Packet& GetData() override
		{
			_data = _var.GetNetOnModified().GetInvokePacket((int)NetworkMessages::EventNetvarUpdated, _var.get());
			return _data;
		}
	private:
		ls_netvar<T>& _var;
	};

	//last state on tick
	template<typename T>
	class ls_netvar : public netvar<T>
	{
	public:
		NetworkEvent<T>& GetNetOnModified() { return netvar<T>::NetOnModified; }
	private:
		void on_modified() override
		{
			netvar<T>::isInvoker = true;
			ls_netvar_msg<T> msg(*this);
			netvar<T>::NetOnModified.InvokeParams(msg, (int)NetworkMessages::EventNetvarUpdated, reactive_ptr<T>::get());
		}

	};
}