#pragma once
#include "ecs/CoreComponents.h"
#include "network/netvar.h"
#include "ecs/component_ref.h"
namespace eng
{
	// TODO : to component, using system

	struct NetTransform : public BehaviourScript
	{
		void OnInit() override;

		ls_netvar<glm::vec3> position;
		ls_netvar<glm::vec3> rotation;
		ls_netvar<glm::vec3> scale;
	private:
		cmp_ref<TransformComponent> transform;
		glm::vec3 Interpolate(const glm::vec3& current, const glm::vec3& last);
	};
}