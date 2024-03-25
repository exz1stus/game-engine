#pragma once
#include <functional>

namespace eng
{
	template<typename... Args>
	class Event
	{
		using EventListener = std::function<void(Args...)>;

	public:
		Event() = default;
		Event(const EventListener& listener)
		{
			Subscribe(listener);
		}
		~Event() = default;

		void Subscribe(const EventListener& listener)
		{
			_listeners.push_back(listener);
		}

		template<typename T>
		void Bind(void (T::* method)(Args...), T* object)
		{
			Subscribe(static_cast<EventListener>([method, object](Args... args) {  (object->*method)(args...); }));
		}

		void Unsubscribe(const EventListener& listener)
		{
			auto it = std::find_if(_listeners.begin(), _listeners.end(), [&](const EventListener& el) {
				return el.target<void(Args...)>() == listener.target<void(Args...)>();
				});

			if (it != _listeners.end())
			{
				_listeners.erase(it);
			}
		}

		template<typename T>
		void Unbind(void (T::* method)(Args...), T* object)
		{
			auto target = [method, object](Args... args) { (object->*method)(args...); };

			Unsubscribe(target);
		}

		void Invoke(Args... args) const
		{
			for (const auto& listener : _listeners)
			{
				listener(args...);
			}
		}

		void operator+=(const EventListener& listener)
		{
			Subscribe(listener);
		}

		void operator-=(const EventListener& listener)
		{
			Unsubscribe(listener);
		}	

		void operator()(Args... args) { Invoke(args...); }

	private:
		std::vector<EventListener> _listeners;
	};
	
	//using Signal = Event<>; // TODO
}