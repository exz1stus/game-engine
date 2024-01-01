#pragma once
#include <functional>

namespace eng
{
	template<typename T , typename... Args>
	class Event
	{
		using EventHandler = std::function<T(Args...)>;

	public:

		Event() = default;
		Event(const EventHandler& handler)
		{
			operator+=(handler);
		}

		~Event() = default;

		void operator+=(const EventHandler& handler)
		{
			_listeners.push_back(handler);
		}
		void operator-=(const EventHandler& handler)
		{
			//_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), handler), _listeners.end());
		}	
		void operator()(Args... args) { Invoke(args...); }

		void Invoke(Args... args)
		{
			for (const auto& handler : _listeners)
			{
				handler(args...);
			}
		}

	private:
		std::vector<EventHandler> _listeners;
	};
}