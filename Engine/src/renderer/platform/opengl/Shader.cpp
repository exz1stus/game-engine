#include "engpch.h"
#include "Shader.h"

#include "glm/gtc/type_ptr.hpp"

namespace eng
{
	const std::string Shader::shaderFolder = "../Engine/assets/shaders/opengl/";
	//const std::string Shader::shaderFolder = "assets/shaders/opengl/";

	Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:_rendererID(0), _name(name)
	{
		_rendererID = CreateShader(vertexSrc, fragmentSrc);
	}
	void Shader::Bind() const
	{
		glUseProgram(_rendererID);
	}
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
			return _uniformLocationCache[name];

		int u_Location = glGetUniformLocation(_rendererID, name.c_str());
		if (u_Location == -1)
		{
			//assert
			std::cout << "Uniform " << name << "doesn't exist" << std::endl;
		}

		_uniformLocationCache[name] = u_Location;

		return u_Location;
	}

	std::shared_ptr<Shader> Shader::LoadShader(const std::string& name, const std::string& shaderLocation)
	{
		std::string vertexSrc;
		std::string fragmentSrc;

		std::ifstream streamVer(shaderLocation + name + ".vert");
		streamVer.seekg(0, std::ios::end);
		//vertexSrc.reserve(streamVer.tellg());
		streamVer.seekg(0, std::ios::beg);
		vertexSrc.assign((std::istreambuf_iterator<char>(streamVer)),
			std::istreambuf_iterator<char>());
		streamVer.close();


		std::ifstream streamFr(shaderLocation + name + ".frag");
		streamFr.seekg(0, std::ios::end);
		//fragmentSrc.reserve(streamFr.tellg());
		streamFr.seekg(0, std::ios::beg);
		fragmentSrc.assign((std::istreambuf_iterator<char>(streamFr)),
			std::istreambuf_iterator<char>());
		streamFr.close();

		//assert
		if (vertexSrc.empty() || fragmentSrc.empty()) std::cout << "failed to parse shader at location : " + shaderLocation + name << std::endl;

		return std::make_shared<Shader>(name, vertexSrc, fragmentSrc);
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
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

			//assert
			std::cout << "Shader error : " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
			std::cout << message << std::endl;

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}