#include "engpch.h"
#include "IndexBuffer.h"

namespace eng
{
	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		: _rendererId(0), _elementsCount(count)
	{
		glGenBuffers(1, &_rendererId);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_rendererId);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}