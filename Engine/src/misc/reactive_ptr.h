#pragma once
#include "events/Event.h"
#include <memory>
#include <type_traits>
namespace eng
{
	template<typename T, typename PtrType>
	class scoped_data_holder
	{
	public:
		scoped_data_holder(PtrType* parent)
			:_parent(parent), _ptr(parent->get_rawptr())
		{
		}

		scoped_data_holder(const scoped_data_holder<T, PtrType>* other) = delete;

		~scoped_data_holder()
		{
			_parent->update();
		}

		T* operator->()
		{
			return _ptr;
		}

		scoped_data_holder<T,PtrType>& operator=(const T& value)
		{
			_parent->set_silent(value);
			return *this;
		}

	private:
		PtrType* _parent;
		T* _ptr;
	};

	template<typename T>
	struct shared_data
	{
		std::shared_ptr<T> _ptr;
		Event<> OnModified;
	};

	template<typename T>
	class reactive_ptr
	{
	public:
		reactive_ptr()
		{
			_shared = std::make_shared<shared_data<T>>();
			_shared->_ptr = std::make_shared<T>();
		}

		reactive_ptr(const reactive_ptr& other)
		{
			_shared = other._shared;
		}

		template<
			typename... Args,
			typename = std::enable_if_t<!std::is_same_v<reactive_ptr, std::decay_t<Args>>...>
		>
		reactive_ptr(Args&&... args)
		{
			_shared = std::make_shared<shared_data<T>>();
			_shared->_ptr = std::make_shared<T>(std::forward<Args>(args)...);
		}

		operator const T* () const { return &get(); }

		const T& operator*() const
		{
			return get();
		}

		scoped_data_holder<T, reactive_ptr<T>> operator->()
		{
			return scoped_data_holder<T, reactive_ptr<T>>(this);
		}

		scoped_data_holder<T, reactive_ptr<T>> getsc()
		{
			return scoped_data_holder<T, reactive_ptr<T>>(this);
		}

		const T& get() const
		{
			return *_shared->_ptr;
		}

		void set(const T& newValue) const
		{
			*_shared->_ptr = newValue;
			_shared->OnModified();
		}

		void update()
		{
			on_modified();
			_shared->OnModified();
		}

		Event<>& GetOnModified() const { return _shared->OnModified; }
	protected:
		virtual void on_modified() {}
	private:
		std::shared_ptr<shared_data<T>> _shared;

		void set_silent(const T& newValue)
		{
			*_shared->_ptr = newValue;
		}

		T* get_rawptr()
		{
			return _shared->_ptr.get();
		}

		friend scoped_data_holder<T, reactive_ptr<T>>;
	};

	template<typename T>
	class reactive_ref
	{
	public:
		reactive_ref() = default;
		reactive_ref(T* ref)
		{
			_ptr = ref;
		}

		reactive_ref(const reactive_ref& other) = delete;

		reactive_ref& operator=(const T& value)
		{
			set(value);
			return *this;
		}

		scoped_data_holder<T, reactive_ref<T>> operator->()
		{
			return scoped_data_holder<T, reactive_ref<T>>(this);
		}

		const T& operator*() const
		{
			return get();
		}

		const T& get() const
		{
			return *_ptr;
		}

		scoped_data_holder<T, reactive_ref<T>> getsc()
		{
			return scoped_data_holder<T, reactive_ref<T>>(this);
		}

		void set(const T& newValue)
		{
			*_ptr = newValue;
			on_modified();
			OnModified();
		}

		void update()
		{
			on_modified();
			OnModified();
		}

		Event<> OnModified;
	protected:
		virtual void on_modified() {}
	private:
		T* _ptr;

		T* get_rawptr()
		{
			return _ptr;
		}

		void set_silent(const T& newValue)
		{
			*_ptr = newValue;
		}
		friend scoped_data_holder<T, reactive_ref<T>>;
	};
}