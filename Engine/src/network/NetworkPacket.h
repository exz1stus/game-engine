#pragma once
#include <vector>
#include "debug/logger/Logger.h"
namespace eng
{
	struct PacketHeader
	{
		int id;
		uint32_t size = 0;
	};

	struct Packet
	{
		PacketHeader header;
		std::vector<uint8_t> body;

		size_t size() const
		{
			return sizeof(header) + body.size() * 1;
		}

		static Packet DeserializePacket(const uint8_t* data, size_t dataSize)
		{
			Packet packet;
			if (dataSize < sizeof(PacketHeader))
			{
				Logger::Error("Data size is too small to contain a valid packet header.");
				return packet;
			}

			std::memcpy(&packet.header, data, sizeof(PacketHeader));
			packet.body.resize(dataSize - sizeof(PacketHeader));
			std::memcpy(packet.body.data(), data + sizeof(PacketHeader), dataSize - sizeof(PacketHeader));

			return packet;
		}


		template<typename DataT>
		friend Packet& operator << (Packet& packet, const DataT& data)
		{
			Logger::Assert(std::is_standard_layout<DataT>::value, "Data is too complex to serialize");

			size_t currentSize = packet.body.size();
			packet.body.resize(currentSize + sizeof(DataT));

			std::memcpy(packet.body.data() + currentSize, &data, sizeof(DataT));

			packet.header.size = packet.size();

			return packet;
		}

		template<typename DataT>
		friend Packet& operator >> (Packet& packet, DataT& data)
		{
			Logger::Assert(std::is_standard_layout<DataT>::value, "Data is too complex to deserialize");

			size_t sizeShift = packet.body.size() - sizeof(DataT);

			std::memcpy(&data, packet.body.data() + sizeShift, sizeof(DataT));

			packet.body.resize(sizeShift);
			packet.header.size = packet.size();

			return packet;
		}

		friend std::ostream& operator << (std::ostream& os, const Packet packet)
		{
			os << "ID:" << int(packet.header.id) << "Size: " << packet.header.size;
			return os;
		}
	};
}