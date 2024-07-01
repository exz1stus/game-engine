#include "network/Client.h"
#include "network/netvar.h"
#include "core/EntryPoint.h"
#include <random>
#include "network/NetworkEvent.h"
#include "renderer/Renderer2D.h"

#include <list>
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

void func(int a, float b)
{
	Logger::Log("{}, {}", a, b);
}

ClientApp::ClientApp(RunningMode mode)
	: Application(mode)
{
	std::shared_ptr<Client> cl = NetworkManager::CreateClient();
	NetworkManager::StartNetworkLoop();

	cl->Connect("127.0.0.1", 7777);

	NetworkEvent<int,float> e;
	
	e += func;
	
	e.Invoke(123,2.018349f);

	while (true)
	{

	}

	/*netvar<int> var;
	auto sc = var.getsc();

	sc = 1;

	sc.end();*/

	/*glm::vec2 qwe = {1,2};

	reactive_ref<glm::vec2> p(&qwe);

	p.OnModified += [&p]() {
		Logger::Log("New Value {}", (*p).x);
	};

	p = { 4.0f, 2.0f };

	reactive_ptr<glm::vec2> rptr;

	rptr.GetOnModified() += []() {
		Logger::Log("Modified");
	};

	reactive_ptr<glm::vec2> rptr2 = rptr;
	reactive_ptr<glm::vec2> rptr3 = rptr2;
	reactive_ptr<glm::vec2> rptr4 = rptr3;
	reactive_ptr<glm::vec2> rptr5 = rptr4;
	reactive_ptr<glm::vec2> rptr6 = rptr5;  

	rptr6.getsc() = { 2,3 };*/
	/*cl.Connect("127.0.0.1", 7777);
	while(true)
	{
		Packet p;
		int x = rand() % 100 + 1;
		p << x;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 20));
		cl.GetConnection()->Send(p);
		cl.Tick();
	}

	cl.Disconnect();*/
}
