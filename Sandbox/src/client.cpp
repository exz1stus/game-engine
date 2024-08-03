//#include "network/Client.h"
//#include "network/netvar.h"
#include "core/EntryPoint.h"
#include "core/eng.h"
//#include <random>
//#include "network/NetworkEvent.h"
//#include "renderer/Renderer2D.h"
//
//#include <list>
#include "ecs/BehaviourScript.h"

using namespace eng;

class ClientApp : public Application
{
public:
	ClientApp(RunningMode mode);
};

eng::Application* eng::CreateApplication()
{
	return new ClientApp(RunningMode::Headless);
}

class Sc1 : public BehaviourScript
{
public:
	void OnInit() override
	{
		value.create(&val);
		Logger::Log("Script 1 init");
		value.OnModified += []() { Logger::Log("modified"); };
	}

	reactive_ref<int> value;
private:
	int val;
};
class Sc2 : public BehaviourScript
{
public:
	void OnInit() override
	{
		Logger::Log("Script 2 init");
	}
};

ClientApp::ClientApp(RunningMode mode)
	: Application(mode)
{
	Entity e;

	auto& transform = e.AddComponent<TransformComponent>();
	auto& scriptHolder = e.AddComponent<ScriptComponent>();
	scriptHolder.AddScript<Sc1>();
	scriptHolder.AddScript<Sc2>();

	auto& sc1 = scriptHolder.GetScript<Sc1>();
	sc1.value = 2;
}
