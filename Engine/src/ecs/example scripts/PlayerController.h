#pragma once
#include "ecs/CoreComponents.h"
namespace eng
{
	class PlayerController : public BehaviourScript
	{
	private:
		void OnUpdate() override;
	};
}