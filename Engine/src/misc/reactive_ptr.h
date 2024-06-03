#pragma once
#include "events/Event.h"
#include <memory>
namespace eng
{
	/*template<typename T>
	class reactive_var
	{
	public:
		reactive_var() : _ptr(nullptr) {};
		reactive_var(T& ptr) : _ptr(&ptr) {}

		const T* get() const { return _cmp; }
		T* get_reactive()
		{
			OnValueAccessed();
			return _ptr;
		}

		operator const T& () const { return *get(); }
		operator const T* () const { return get(); }

		T* operator->()
		{
			return get_reactive();
		}
		Event<> OnValueAccessed;
	protected:
		virtual void onValueAccessed() = 0;
		T _ptr;
	};*/

	template<typename T>
	class reactive_var
	{
	public:
		reactive_var() : _ptr(nullptr) {};

		const T* get() const = 0;
		T* get_reactive() = 0;

		operator const T& () const = 0;
		operator const T* () const = 0;

		T* operator->()
		{
			return get_reactive();
		}
		Event<> OnValueAccessed;
	protected:
		virtual void on_value_accessed () = 0;
		T _ptr;
	};

	template<typename T>
	class reactive_ptr : public reactive_var<std::unique_ptr<T>>
	{
		virtual void on_value_accessed() = 0;
	};

	template<typename T>
	class reactive_ref : public reactive_var<T*>
	{
		virtual void on_value_accessed() = 0;
	};
}