#pragma once
#include "Buffer.h"
namespace eng
{
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, uint32_t size);

		const BufferLayout& GetLayout() const { return _layout; }
		void SetLayout(const BufferLayout& layout) { _layout = layout; }

	private:
		uint32_t _rendererID;
		BufferLayout _layout;
	};
}

