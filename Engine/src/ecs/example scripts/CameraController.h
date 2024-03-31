#pragma once
#include "ecs/CoreComponents.h"
namespace eng
{
	class CameraController : public BehaviourScript
	{
		void OnInit() override;
		void OnUpdate() override;
	};
}

