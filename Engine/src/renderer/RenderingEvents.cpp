#include "engpch.h"
#include "RenderingEvents.h"
namespace eng
{
	Event<uint16_t, uint16_t> RenderingEvents::OnWindowResized;
	Event<> RenderingEvents::OnWindowClosed;
}