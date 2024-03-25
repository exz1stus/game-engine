#include "engpch.h"
#include "Shader.h"
#include <glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace eng
{
	Shader::Shader(const std::string& name)
		:_rendererID(0), _name(name)
	{}
	void Shader::Bind() const
	{
		glUseProgram(_rendererID);
	}
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
	void Shader::SetInt(const std::string& name, int value)
	{
		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}
	void Shader::SetArrInt(const std::string& name, const int* arr, const uint32_t length)
	{
		GLint location = GetUniformLocation(name);
		glUniform1iv(location, GLsizei(length), arr);
	}
	void Shader::SetVecInt(const std::string& name, const std::vector<int>& vec)
	{
		GLint location = GetUniformLocation(name);
		glUniform1iv(location, GLsizei(vec.size()), &vec[0]);
	}
	void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);

	}
	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
			return _uniformLocationCache[name];

		int u_Location = glGetUniformLocation(_rendererID, name.c_str());
		if (u_Location == -1)
		{
			Logger::Error("Uniform " + name + "doesn't exist");
		}

		_uniformLocationCache[name] = u_Location;

		return u_Location;
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;

		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));

			glGetShaderInfoLog(id, length, &length, message);

			
			Logger::Error("Shader error : " + (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
			Logger::Error(message);

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	uint32_t Shader::CreateShader(const ShaderSource& shaderSources)
	{
		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, shaderSources.vert);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, shaderSources.frag);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		_rendererID = program;
		return program;
	}
}