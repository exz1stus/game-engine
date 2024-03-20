#pragma once
#include "events/Event.h"

namespace eng
{
	struct RenderingEvents
	{
		static Event<uint16_t, uint16_t> OnWindowResized;
		static Event<> OnWindowClosed;

		static Event<> OnDrawUI;
	};
}