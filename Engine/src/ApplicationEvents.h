#pragma once
#include "events/Event.h"
namespace eng
{
	struct ApplicationEvents
	{
		static Event<> OnInit;
		static Event<> OnStart;
		static Event<> OnUpdate;
		static Event<> OnRender;
		static Event<> OnQuit;
	};
}

