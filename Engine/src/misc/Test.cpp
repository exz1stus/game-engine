#include "engpch.h"
#include "ecs/component_ptr.h"
#include "ecs/CoreComponents.h"
#include "renderer/platform/opengl/RenderingAPI.h"
#include "renderer/Renderer2D.h"
#include "Utilities.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "events/Event.h"


namespace eng
{
	void fff(std::function<void(int,float)>)
	{

	}
	/*void fff(void (*func)(int, float))
	{

	}*/
	int a = 2;
	int&& getInt() { return 2; }

	static entt::observer observer;
	void test()
	{
		/*observer.connect(SceneManager::GetCurrentScene()->_registry, entt::collector.update<TransformComponent>());
		Entity e;
		TransformComponent& cmp = e.AddComponent<TransformComponent>();
		cmp_ref<TransformComponent> ptr(cmp,e);
		cmp_ref<TransformComponent> ptr1(cmp,e);

		ptr = ptr1;
		ptr->position.x = 100.0f;
		fff(ptr);
		for (Entity e : observer)
		{
			print(e.GetComponent<TransformComponent>().position.x);
		}*/

		Event<int, float> e;
		fff(e);
	}
}