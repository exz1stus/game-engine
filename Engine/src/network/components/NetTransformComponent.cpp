#include "engpch.h"
#include "NetTransformComponent.h"
namespace eng
{
	void NetTransform::OnInit()
	{
		transform = GetComponentReactive<TransformComponent>();

		position.GetOnModified() += [this]() {
			transform->position = Interpolate(transform->position, position.get());
		};
		rotation.GetOnModified() += [this]() {
			transform->rotation = rotation.get();
			};
		scale.GetOnModified() += [this]() {
			transform->scale = scale.get();
		};
	}

	glm::vec3 NetTransform::Interpolate(const glm::vec3& current, const glm::vec3& last)
	{
		return glm::mix(current, last, 0.5f);
	}
}