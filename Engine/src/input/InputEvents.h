#pragma once
#include "events/Event.h"
namespace eng
{
	class InputEvents
	{
	public:
		static Event<float, float> OnMouseMoved;
	};
}

