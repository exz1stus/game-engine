#include "engpch.h"
#include "NetSpriteRenderer.h"

namespace eng
{
	void NetSpriteRenderer::OnInit()
	{
		sprite = GetComponentReactive<SpriteRendererComponent>();

		color.GetOnModified() += [this]() {
			sprite->color = color.get();
			};
		alpha.GetOnModified() += [this]() {
			sprite->alpha = alpha.get();
			};

		//texture.GetOnModified() += [this]() {
		//	//TODO: implement sending only id of the texture asset
		//	//TODO: asset manager
		//	};
	}
}