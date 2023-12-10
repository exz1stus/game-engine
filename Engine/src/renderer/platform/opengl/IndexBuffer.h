#pragma once
#include "Buffer.h"
namespace eng
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		const uint32_t GetCount() const { return _elementsCount; }

	private:
		uint32_t _rendererId;
		uint32_t _elementsCount;
	};
}