#pragma once
#include "ecs/Entity.h"
#include "misc/reactive_ptr.h"

namespace eng
{
	template <typename Component>
	class cmp_ref : public reactive_ref<Component>
	{
	public:
		cmp_ref(Entity entity) : id(entity), reactive_ptr<Component>(id.GetComponent<Component>()) {}
		cmp_ref(Component& cmp, Entity entity) : id(entity), reactive_ptr<Component>(cmp) {}
	private:
		void OnValueAccessed() override
		{
			id.Patch<Component>();
		}
		Entity id;
	};
	/*template <typename Component>
	class cmp_ref
	{
	public:
		cmp_ref() : _cmp(nullptr) {};
		cmp_ref(Entity entity) : id(entity) , _cmp(id.GetComponent<Component>()) {}
		cmp_ref(Component& cmp, Entity entity) : id(entity), _cmp(&cmp) {}
		
		const Component* get() const { return _cmp; }
		Component* get_reactive()
		{
			id.Patch<Component>();
			return _cmp;
		}

		operator const Component&() const { return *get(); }
		operator const Component*() const { return get(); }

		Component* operator->()
		{
			return get_reactive();		
		}	
	private:
		Entity id;
		Component* _cmp;
	};*/
}