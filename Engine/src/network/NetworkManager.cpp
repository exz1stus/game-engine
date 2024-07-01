#include "engpch.h"
#include "NetworkManager.h"
#include "GameTime.h"
#include <thread>
#include <memory>

#define ENET_IMPLEMENTATION
#include "network/Client.h"
#include "network/Server.h"

#include "network/NetworkRegistry.h"
//#include "network/NetworkEvent.h"

namespace eng
{
	struct ClientRpcHeader;

	uint8_t NetworkManager::_tickrate = 20;

	std::queue<Packet> NetworkManager::_netEventsQueue;
	std::queue<Packet> NetworkManager::_serverNetEventsQueue;
	HostState NetworkManager::_state = HostState::Offline;

	std::shared_ptr<Client> NetworkManager::_client;
	std::shared_ptr<Server> NetworkManager::_internalServer;


	static std::unique_ptr<std::thread> networkThread;
	static std::mutex networkMutex;
	static std::atomic<bool> running = false;

	static std::thread::id networkThreadID;

	void NetworkManager::Init()
	{
		if (enet_initialize() != 0) //TODO : implement network api interface
		{
			Logger::CriticalError("Failed to initialize ENet!");
		}
	}

	void NetworkManager::Quit()
	{
		running = false;

		if (networkThread->joinable())
			networkThread->join();
	}

	void NetworkManager::StartNetworkLoop()
	{
		if (running)
		{
			Logger::Error("Network Loop is already running");
			return;
		}

		if ((_client != nullptr && !_client->IsCreated()) &&
			(_internalServer != nullptr && !_internalServer->IsCreated()))
		{
			Logger::Error("Neither server nor client hasn't started");
			return;
		}
		running = true;
		networkThread = std::make_unique<std::thread>(NetworkLoop);
	}

	std::shared_ptr<Client> NetworkManager::CreateClient()
	{
		if (HasClient())
		{
			Logger::Error("Client is already running");
			return nullptr;
		}

		_client = std::make_shared<Client>();

		if (_state == HostState::Offline)
			_state = HostState::OnlyClient;
		if (_state == HostState::OnlyServer)
			_state = HostState::ClientServer;

		return _client;
	}

	std::shared_ptr<Server> NetworkManager::CreateInternalServer()
	{
		if (HasServer())
		{
			Logger::Error("Internal server is already running");
			return nullptr;
		}

		_internalServer = std::make_shared<Server>();

		if (_state == HostState::Offline)
			_state = HostState::OnlyServer;
		if (_state == HostState::OnlyClient)
			_state = HostState::ClientServer;

		return _internalServer;
	}

	void NetworkManager::AddNetworkEvent(Packet& p)
	{
		if (HasClient())
		{
			_netEventsQueue.push(p);
			return;
		}

		if (HasServer() && 
			(_state == HostState::OnlyServer || IsCallingFromServerThread()))
				_serverNetEventsQueue.push(p);
	}

	void NetworkManager::OnRecieved(Packet& p)
	{
		switch ((NetworkMessages)p.header.id)
		{
		case NetworkMessages::EventClientRPC:
			if (HasServer())
			{
				size_t idShift = sizeof(size_t);

				ClientRpcHeader header = p.GetFromEnd<ClientRpcHeader>(idShift);

				if(HasClient())
				{
					size_t localClient = _client->_hostID;
					_internalServer->ClientRpc(p, header, localClient);
				}
				else
					_internalServer->ClientRpc(p, header);
			}
			if (HasClient())
			{
				size_t id = p.PopFromEnd<size_t>();

				inetevent_reciever* reciever = NetworkRegistry<inetevent_reciever>::GetByID(id);
				reciever->on_recieved(p);
			}
			break;
		case NetworkMessages::EventNetvarUpdated:
			break;
		default:
			break;
		}
	}

	size_t NetworkManager::GetHostID()
	{
		if (IsCallingFromServerThread() && HasServer())
			return 0;

		if (HasClient())
			return _client->_hostID;
	}

	bool NetworkManager::IsCallingFromServerThread()
	{
		if(running && HasServer())
			return std::this_thread::get_id() == networkThreadID;
	}

	void NetworkManager::NetworkLoop()
	{
		networkThreadID = std::this_thread::get_id();

		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;

		auto tickInterval = std::chrono::milliseconds(1000 / _tickrate);
		while (running)
		{
			start = std::chrono::steady_clock::now();

			Tick();
			std::this_thread::sleep_until(start + tickInterval);

			end = std::chrono::steady_clock::now();

			double tickTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			//Logger::Log("Network Tick, TPS: {} ", (float)1000 / tickTime);
		}
	}
	void NetworkManager::Tick()
	{
		if (HasClient() && _client->_hostID != 0)
		{
			while (!_netEventsQueue.empty())
			{
				Packet& p = _netEventsQueue.front();
				_client->GetConnection()->Send(p);
				_netEventsQueue.pop();
			}
			_client->Tick();
		}


		if (HasServer())
		{
			while (!_serverNetEventsQueue.empty())
			{
				Packet& p = _serverNetEventsQueue.front();
				_internalServer->ClientRpc(p, {0});
				_serverNetEventsQueue.pop();
			}
			_internalServer->Tick();
		}
	}
}
