#pragma once
#include "ecs/CoreComponents.h"
#include "network/netvar.h"
#include "ecs/component_ref.h"

namespace eng
{
	struct NetSpriteRenderer : public BehaviourScript
	{
		void OnInit() override;

		netvar<glm::vec3> color;
		netvar<float> alpha;
		//netvar<Texture2D> texture;

	private:
		cmp_ref<SpriteRendererComponent> sprite;
	};
}