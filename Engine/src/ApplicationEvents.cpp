#include "engpch.h"
#include "ApplicationEvents.h"

namespace eng
{
	Event<> ApplicationEvents::OnInit;
	Event<> ApplicationEvents::OnStart;
	Event<> ApplicationEvents::OnUpdate;
	Event<> ApplicationEvents::OnRender;
	Event<> ApplicationEvents::OnQuit;
}