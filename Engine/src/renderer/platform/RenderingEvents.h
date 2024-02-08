#pragma once
#include "events/Event.h"

namespace eng
{
	class RenderingEvents
	{
	public:
		static Event<uint16_t, uint16_t> OnWindowResized;
	};
}