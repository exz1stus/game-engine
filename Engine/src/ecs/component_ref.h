#pragma once
#include "ecs/Entity.h"
#include "misc/reactive_ptr.h"

namespace eng
{
	template <typename Component>
	class cmp_ref : public reactive_ref<Component>
	{
	public:
		cmp_ref() = default;
		cmp_ref(Entity entity) : id(entity), reactive_ref<Component>(id.GetComponent<Component>()) {}
		cmp_ref(Component& cmp, Entity entity) : id(entity), reactive_ref<Component>(&cmp) {}
	private:
		void on_modified() override
		{
			id.Patch<Component>();
		}
		Entity id;
	};
}