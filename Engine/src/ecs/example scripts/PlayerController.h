#pragma once
#include "ecs/CoreComponents.h"
namespace eng
{
	class PlayerController : public BehaviourScript
	{
	private:
		void OnInit() override;
		void OnUpdate() override;
	};
}