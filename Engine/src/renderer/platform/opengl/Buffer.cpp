#include "engpch.h"
#include "Buffer.h"


eng::BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
	: _bufferElements(elements)
{
	eng::BufferLayout::CalculateOffsetsAndStride();
}

eng::BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
	: Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
{}

void eng::BufferLayout::CalculateOffsetsAndStride()
{
	size_t offset = 0;
	_stride = 0;
	for (auto& element : _bufferElements)
	{
		element.Offset = offset;
		offset += element.Size;
		_stride += element.Size;
	}
}
