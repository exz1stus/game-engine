#include "core/EntryPoint.h"
#include "network/Client.h"
#include "network/NetworkManager.h"
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

ServerApp::ServerApp(RunningMode mode)
    :Application(mode)
{
    NetworkManager::StartInternalServer();

    /*Client cl;

    cl.Connect("127.0.0.1", 7777);
    while (true)
        cl.Tick();

    cl.Disconnect();*/
}
