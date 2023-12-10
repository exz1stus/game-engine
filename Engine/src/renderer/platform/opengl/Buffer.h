#pragma once
#include "engpch.h"
#include <glad.h>

namespace eng
{
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4,
		Mat4,
		Int
	};

	static uint32_t GetShaderDataTypeSize(const ShaderDataType type)
	{
		switch (type)
		{
		case eng::ShaderDataType::Float:	return sizeof(float);
		case eng::ShaderDataType::Float2:	return sizeof(float) * 2;
		case eng::ShaderDataType::Float3:	return sizeof(float) * 3;
		case eng::ShaderDataType::Float4:	return sizeof(float) * 4;
		case eng::ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		case eng::ShaderDataType::Int:		return sizeof(int);

		default:
			//assert
			return 0;
		}
	}
	class BufferElement
	{
	public:
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);
		~BufferElement() = default;

		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements);
		BufferLayout() = default;
		~BufferLayout() = default;

		const uint32_t GetStride() const { return _stride; }

		std::vector<BufferElement>::iterator begin() { return _bufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return _bufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _bufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _bufferElements.end(); }

	private:
		void CalculateOffsetsAndStride();

		std::vector<BufferElement> _bufferElements;
		uint32_t _stride = 0;
	};
}