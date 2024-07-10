#pragma once
#include <queue>
#include "NetworkPacket.h"
#include "NetworkMessage.h"
namespace eng
{

	class Server;
	class Client;

	enum class HostState
	{
		Offline,
		OnlyServer,
		OnlyClient,
		ClientServer,
	};

	enum class NetworkMessages
	{
		AssignIDToClient,

		EventClientRPC,
		EventNetvarUpdated,
	};

	class NetworkManager
	{
	public:
		static void Init();
		static void Quit();
		static void StartNetworkLoop();
		static std::shared_ptr<Client> CreateClient();
		static std::shared_ptr<Server> CreateInternalServer();
		
		static void AddNetworkEvent(NetworkMessage& msg);

		static void OnRecieved(Packet& p);

		static size_t GetHostID();

		static bool IsCallingFromServerThread();

		static void CustomTick(NetworkMessage& p);
	private:
		static bool HasServer() { return _state == HostState::OnlyServer || _state == HostState::ClientServer; }
		static bool HasClient() { return _state == HostState::OnlyClient || _state == HostState::ClientServer; }

		static void NetworkLoop();
		static void Tick();
		static uint8_t _tickrate;
		static HostState _state;

		static std::queue<NetworkMessage> _netEventsQueue;
		static std::queue<NetworkMessage> _serverNetEventsQueue;

		static std::shared_ptr<Client> _client;

		static std::shared_ptr<Server> _internalServer;

	};
}
