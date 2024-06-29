#pragma once
#include <queue>

namespace eng
{

	class Server;

	class NetworkManager
	{
	public:
		static void Init();
		static void Quit();
		static void StartInternalServer();
		//static void ClientRpc();
		//static void ServerCommand();
	private:
		static void NetworkLoop();
		static void Tick();
		static uint8_t _tickrate;
		static std::unique_ptr<Server> _internalServer;
	};
}
