#include "engpch.h"
#include "NetworkManager.h"
#include "GameTime.h"
#include <thread>
#include <memory>

#define ENET_IMPLEMENTATION
#include "network/Server.h"

namespace eng
{
	uint8_t NetworkManager::_tickrate = 20;

	std::unique_ptr<Server> NetworkManager::_internalServer;


	static std::unique_ptr<std::thread> networkThread;
	static std::mutex networkMutex;
	static std::atomic<bool> running = true;

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

	void NetworkManager::StartInternalServer()
	{
		_internalServer = std::make_unique<Server>();
		if (_internalServer->IsCreated())
			networkThread = std::make_unique<std::thread>(NetworkLoop); //TODO : multithreading manager
	}

	void NetworkManager::NetworkLoop()
	{
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
			Logger::Log("Server Tick, TPS: {} ", (float)1000 / tickTime);
		}
	}
	void NetworkManager::Tick()
	{
		_internalServer->Tick();
	}
}
