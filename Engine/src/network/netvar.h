#pragma once
#include "misc/reactive_ptr.h"
#include "NetworkManager.h"
#include "NetworkRegistry.h"
#include "NetworkEvent.h"
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
	private:
		//uint32_t id;

		NetworkEvent<T> NetOnModified;

		bool isInvoker = false; // EEW WWQ QWE

		void on_modified() override
		{
			isInvoker = true;
			NetOnModified.InvokeParams((int)NetworkMessages::EventNetvarUpdated, reactive_ptr<T>::get());
		}
	};
}