#include "engpch.h"
#include "VertexArray.h"

#include <glad.h>

namespace eng
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		/*case ShaderDataType::Mat3:     return GL_FLOAT;*/
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		/*case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;*/
		}

		return 0;
	}

	VertexArray::VertexArray()
		:_rendererID(0)
	{
		glGenVertexArrays(1, &_rendererID);
	}

	
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_rendererID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(_rendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		_vertexBuffer = vertexBuffer;

		this->Bind();
		vertexBuffer->Bind();

		SetLayout(vertexBuffer->GetLayout());
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		_indexBuffer = indexBuffer;
	}

	void VertexArray::SetLayout(const BufferLayout& layout)
	{
		int i = 0;
		for (const auto & element : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.Size / sizeof(ShaderDataTypeToOpenGLBaseType(element.Type)), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, layout.GetStride(), (const void*)element.Offset); //count
			i++;
		}
	}
}