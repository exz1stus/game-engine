#include "engpch.h"
#include "NetworkManager.h"
#include "GameTime.h"
#include <thread>
#include <memory>

#define ENET_IMPLEMENTATION
#include "network/Client.h"
#include "network/Server.h"

#include "network/NetworkRegistry.h"
#include "netvar.h"

namespace eng
{
	struct NetworkStats
	{
		uint32_t packetsReceived;
		uint32_t packetsLost;
		uint32_t currentTick;
	};

	static NetworkStats netStats;

	struct ClientRpcHeader;

	uint8_t NetworkManager::_tickrate = 60;

	std::queue<NetworkMessage> NetworkManager::_netEventsQueue;
	std::queue<NetworkMessage> NetworkManager::_serverNetEventsQueue;
	HostState NetworkManager::_state = HostState::Offline;

	std::shared_ptr<Client> NetworkManager::_client;
	std::shared_ptr<Server> NetworkManager::_internalServer;

	static std::unique_ptr<std::thread> networkThread;
	static std::mutex networkMutex;
	static std::atomic<bool> running = false;

	static bool apiInitialized = false;

	static std::thread::id networkThreadID;

	static size_t clientID = 0;

	void NetworkManager::Init()
	{
		if (enet_initialize() != 0) //TODO : implement network api interface
		{
			Logger::CriticalError("Failed to initialize ENet!");
		}

		apiInitialized = true;
	}

	void NetworkManager::Quit()
	{
		if (!running)
			return;

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
		Logger::Assert(apiInitialized, "Client creation : Network loop isn't running");

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
		Logger::Assert(apiInitialized, "Server creation : Network loop isn't running");

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

	void NetworkManager::AddNetworkEvent(NetworkMessage& p)
	{
		if (HasClient() && _state != HostState::ClientServer)
		{
			_netEventsQueue.push(p);
			return;
		}

		if (HasServer() /*&&
			(_state == HostState::OnlyServer || IsCallingFromServerThread())*/)
			_serverNetEventsQueue.push(p);
	}

	void NetworkManager::OnReceived(Packet& p)
	{
		switch ((NetworkMessages)p.header.id)
		{
		case NetworkMessages::EventNetvarUpdated:
		case NetworkMessages::EventClientRPC:
			if (HasServer())
			{
				size_t idShift = sizeof(size_t);
				ClientRpcHeader header;
				//try
				//{
					header = p.GetFromEnd<ClientRpcHeader>(idShift);
				//}
				//catch (...) {
					//netStats.packetsLost++;
					//Logger::Error("Lost a packet");
					//break;
				//}

				netStats.packetsReceived++;

				if (HasClient())
				{
					size_t localClient = _client->_hostID;
					_internalServer->ClientRpc(p, header, localClient);
				}
				else
					_internalServer->ClientRpc(p, header);
			}
			if (HasClient())
			{
				size_t id;
				//try
				//{
					id = p.PopFromEnd<size_t>();
				//}
				//catch (...)
				//{
					//netStats.packetsLost++;
					//Logger::Error("Lost a packet");
					//break;
				//}

				inetevent_receiver* receiver = NetworkRegistry<inetevent_receiver>::GetByID(id);
				receiver->on_received(p);
			}
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
		if (running && HasServer())
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
			if (clientID == 0)
				clientID = _client->_hostID;


			while (!_netEventsQueue.empty())
			{
				auto& msg = _netEventsQueue.front();
				_client->GetConnection()->Send(msg.GetData());
				_netEventsQueue.pop();
			}
			_client->Tick();
		}

		if (HasServer())
		{
			while (!_serverNetEventsQueue.empty())
			{
				auto& msg = _serverNetEventsQueue.front();
				_internalServer->ClientRpc(msg.GetData(), { 0 }, clientID);
				_serverNetEventsQueue.pop();
			}
			_internalServer->Tick();
		}

		netStats.currentTick++;
		if (netStats.currentTick > _tickrate)
			netStats.currentTick = 0;

		//Logger::Log("Tick : {} \n Packets Lost : {}", netStats.currentTick, netStats.packetsLost);
	}

	void NetworkManager::CustomTick(NetworkMessage& msg)
	{
		if (HasClient() && _client->_hostID != 0)
		{
			if (clientID == 0)
				clientID = _client->_hostID;

			_client->GetConnection()->Send(msg.GetData());
			_client->Tick();
		}

		if (HasServer())
		{
			_internalServer->ClientRpc(msg.GetData(), { 0 }, clientID);
			_internalServer->Tick();
		}
	}
}
