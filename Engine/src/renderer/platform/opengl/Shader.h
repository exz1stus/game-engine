#pragma once
#include <glm/glm.hpp>
#include <glad.h>

namespace eng
{
	class Shader
	{
	public:
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader() = default;

		void Bind() const;
		void Unbind() const;

		//void SetInt(const std::string& name, int value);
		//void SetIntArray(const std::string& name, int* values, uint32_t count);
		//void SetFloat(const std::string& name, float value);
		//void SetFloat2(const std::string& name, const glm::vec2& value);
		//void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		int GetUniformLocation(const std::string& name);

		static std::shared_ptr<Shader> LoadShader(const std::string& name, const std::string& shaderLocation = shaderFolder);



	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		uint32_t _rendererID;
		std::unordered_map<std::string, int> _uniformLocationCache;
		const std::string _name;

		const static std::string shaderFolder;

	};
}