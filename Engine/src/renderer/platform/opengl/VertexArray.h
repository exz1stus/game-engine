#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace eng
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();


		void Bind() const;
		void Unbind() const;

		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const  std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return _vertexBuffer; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }

		//const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		//const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		void SetLayout(const BufferLayout& layout);

		uint32_t _rendererID;
		uint32_t _vertexBufferIndex = 0;
		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer> _indexBuffer;
	};

}

