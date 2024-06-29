#pragma once
#include <enet.h>
#include "network/Host.h"
namespace eng
{
	class EnetHost : public IHost
	{
	public:
		EnetHost();
		~EnetHost();
		void Tick() override;
		bool IsCreated() const override { return _host != nullptr; }
	protected:
		ENetHost* _host;
	};

	class EnetClient : public EnetHost
	{
	public:
		EnetClient();
		//~EnetClient() = default;
	};
	class EnetServer : public EnetHost
	{
	public:
		EnetServer();
		//~EnetServer() = default;
	};
}