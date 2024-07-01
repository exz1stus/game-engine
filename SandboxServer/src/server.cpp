#include "core/EntryPoint.h"
#include "network/Client.h"
#include "network/NetworkManager.h"
#include "network/NetworkEvent.h"
using namespace eng;

class ServerApp : public Application
{
public:
    ServerApp(RunningMode mode);
};

eng::Application* eng::CreateApplication()
{
    return new ServerApp(RunningMode::Headless);
}

void func(int a, float b)
{
    Logger::Log("{}, {}", a, b);
}

ServerApp::ServerApp(RunningMode mode)
    :Application(mode)
{
    NetworkManager::CreateInternalServer();
    NetworkManager::StartNetworkLoop();

    //std::shared_ptr<Client> cl = NetworkManager::CreateClient();

    NetworkEvent<int, float> e;

    e += func;

    while (1)
    {
        e(999, 99.99f);
        Sleep(1000);
    }

    /*cl->Connect("127.0.0.1", 7777);
    while (true)
        cl->Tick();

    cl->Disconnect();*/
}
