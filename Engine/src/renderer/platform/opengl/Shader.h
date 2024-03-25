#pragma once
#include <glm/glm.hpp>

namespace eng
{
	struct ShaderSource
	{
		std::string frag;
		std::string vert;
	};
	
	class Shader
	{
	public:
		Shader(const std::string& name);
		~Shader() = default;

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetArrInt(const std::string& name, const int* arr, const uint32_t length);
		void SetVecInt(const std::string& name, const std::vector<int>& vec);
		//void SetIntArray(const std::string& name, int* values, uint32_t count);
		//void SetFloat(const std::string& name, float value);
		//void SetFloat2(const std::string& name, const glm::vec2& value);
		//void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		int GetUniformLocation(const std::string& name);
		uint32_t CreateShader(const ShaderSource& shaderSources);
		
	private:
		uint32_t CompileShader(uint32_t type, const std::string& source);

		uint32_t _rendererID;
		std::unordered_map<std::string, int> _uniformLocationCache;
		const std::string _name;

		const static std::string shaderFolder;

	};
}