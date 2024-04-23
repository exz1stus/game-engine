#pragma once
#include "ecs/Entity.h"

namespace eng
{
	template <typename Component>
	class cmp_ref
	{
	public:
		cmp_ref() : _cmp(nullptr) {};
		cmp_ref(Entity entity) : id(entity) , _cmp(id.GetComponent<Component>()) {}
		cmp_ref(Component& cmp, Entity entity) : id(entity), _cmp(&cmp) {}
		
		const Component* get_readonly() const { return _cmp; }
		Component* get()
		{
			id.Patch<Component>();
			return _cmp;
		}

		operator const Component&() const { return *get_readonly(); }
		operator const Component*() const { return get_readonly(); }

		Component* operator->()
		{
			return get();		
		}	
	private:
		Entity id;
		Component* _cmp;
	};
}