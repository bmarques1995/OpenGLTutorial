#include "Shader.h"
#include <glad\glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexFilepath, std::string fragmentFilepath) 
{
	std::vector<ShaderInitializer> shaders;
	shaders.push_back({GL_VERTEX_SHADER, vertexFilepath});
	shaders.push_back({GL_FRAGMENT_SHADER, fragmentFilepath});
	m_ProgramID = CreateShader(shaders);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& uniformName, float value)
{
	glUniform1f(GetUniformLocation(uniformName), value);
}

void Shader::SetUniform2f(const std::string& uniformName, const glm::vec2& value)
{
	glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
}

void Shader::SetUniform3f(const std::string& uniformName, const glm::vec3& value)
{
	glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z);
}

void Shader::SetUniform4f(const std::string& uniformName, const glm::vec4& value)
{
	glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1d(const std::string& uniformName, int value)
{
	glUniform1i(GetUniformLocation(uniformName), value);
}

void Shader::SetUniform2d(const std::string& uniformName, const glm::ivec2& value)
{
	glUniform2i(GetUniformLocation(uniformName), value.r, value.g);
}

void Shader::SetUniform3d(const std::string& uniformName, const glm::ivec3& value)
{
	glUniform3i(GetUniformLocation(uniformName), value.r, value.g, value.b);
}

void Shader::SetUniform4d(const std::string& uniformName, const glm::ivec4& value)
{
	glUniform4i(GetUniformLocation(uniformName), value.r, value.g, value.b, value.a);
}

void Shader::SetUniform1u(const std::string& uniformName, unsigned value)
{
	glUniform1ui(GetUniformLocation(uniformName), value);
}

void Shader::SetUniform2u(const std::string& uniformName, const glm::uvec2& value)
{
	glUniform2ui(GetUniformLocation(uniformName), value.s, value.t);
}

void Shader::SetUniform3u(const std::string& uniformName, const glm::uvec3& value)
{
	glUniform3ui(GetUniformLocation(uniformName), value.s, value.t, value.p);
}

void Shader::SetUniform4u(const std::string& uniformName, const glm::uvec4& value)
{
	glUniform4ui(GetUniformLocation(uniformName), value.s, value.t, value.p, value.q);
}

void Shader::SetUniformMat2f(const std::string& uniformName, const glm::mat2& value)
{
	glUniformMatrix2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat2x3f(const std::string& uniformName, const glm::mat2x3& value)
{
	glUniformMatrix2x3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat2x4f(const std::string& uniformName, const glm::mat2x4& value)
{
	glUniformMatrix2x4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat3x2f(const std::string& uniformName, const glm::mat3x2& value)
{
	glUniformMatrix3x2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat3f(const std::string& uniformName, const glm::mat3& value)
{
	glUniformMatrix3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat3x4f(const std::string& uniformName, const glm::mat3x4& value)
{
	glUniformMatrix3x4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat4x2f(const std::string& uniformName, const glm::mat4x2& value)
{
	glUniformMatrix4x2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat4x3f(const std::string& uniformName, const glm::mat4x3& value)
{
	glUniformMatrix4x3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMat4f(const std::string& uniformName, const glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

std::string Shader::ReadFile(const std::string& filepath)
{
	std::ifstream fileStream;
	try 
	{
		fileStream.open(filepath);
	}
	catch (const std::ifstream::failure& e) 
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
	std::stringstream strStream;
	std::string line;
	while (getline(fileStream, line))
		strStream << line << '\n';
	return strStream.str();
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];
	int location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
	m_UniformLocationCache[uniformName] = location;
	return location;
}

unsigned Shader::CreateShader(std::vector<ShaderInitializer> shaderFilepath)
{
	unsigned program = glCreateProgram();
	std::vector<unsigned> shaders;

	for (auto& shader : shaderFilepath) 
	{
		std::string shaderSource = ReadFile(shader.ShaderFilepath);
		shaders.push_back(CompileShader(shaderSource, shader.Type));
	}

	for (auto& shader : shaders)
		glAttachShader(program, shader);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (success != GL_TRUE) 
	{
		int errorLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLength);
		char* infoLog = new char[(size_t)errorLength + 1];
		glGetProgramInfoLog(program, errorLength, &errorLength, infoLog);
		std::cout << "Error program linking\n"<< infoLog << std::endl;
		delete[] infoLog;
	}

	for (auto& shader : shaders)
		glDeleteShader(shader);
	return program;
}

unsigned Shader::CompileShader(std::string shaderSource, unsigned shaderType)
{
	unsigned shader = glCreateShader(shaderType);
	const char* shaderSourceCStr = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceCStr, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE) 
	{
		int errorLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		char* infoLog = new char[(size_t)errorLength + 1];
		glGetShaderInfoLog(shader, errorLength, &errorLength, infoLog);
		std::cout << "Error " << StringShaderType(shaderType) << " shader compilation failed" << std::endl;
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}

	return shader;
}

std::string Shader::StringShaderType(unsigned shaderType)
{
	std::unordered_map<unsigned, std::string> shaderMapped;
	shaderMapped[GL_VERTEX_SHADER] = "vertex";
	shaderMapped[GL_FRAGMENT_SHADER] = "fragment";
	shaderMapped[GL_GEOMETRY_SHADER] = "geometry";

	if (shaderMapped.find(shaderType) == shaderMapped.end())
		return "";
	return shaderMapped[shaderType];
}
