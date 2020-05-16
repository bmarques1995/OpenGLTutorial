#include "Shader.h"
#include "../ErrorHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string vertexFilepath, std::string fragmentFilepath)
	: m_VertexShaderFilepath(vertexFilepath), m_FragmentShaderFilepath(fragmentFilepath)
{
	ShaderProgramSource programSource = 
	{
		ReadShaderFile(m_VertexShaderFilepath), 
		ReadShaderFile(m_FragmentShaderFilepath)
	};
	m_RendererID = CreateShader(programSource.VertexSourceCode, programSource.FragmentSourceCode);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
}

void Shader::Unbind() const
{
}

void Shader::SetUniform1f(const std::string& uniformName, float value)
{
	GLCall(glUniform1f(GetUniformLocation(uniformName), value));
}

void Shader::SetUniform2f(const std::string& uniformName, const glm::vec2& value)
{
	GLCall(glUniform2f(GetUniformLocation(uniformName), value.x, value.y));
}

void Shader::SetUniform3f(const std::string& uniformName, const glm::vec3& value)
{
	GLCall(glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z));
}

void Shader::SetUniform4f(const std::string& uniformName, const glm::vec4& value)
{
	GLCall(glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
}

void Shader::SetUniform1i(const std::string& uniformName, int value)
{
	GLCall(glUniform1i(GetUniformLocation(uniformName), value));
}

void Shader::SetUniform2i(const std::string& uniformName, const glm::ivec2& value)
{
	GLCall(glUniform2i(GetUniformLocation(uniformName), value.x, value.y));
}

void Shader::SetUniform3i(const std::string& uniformName, const glm::ivec3& value)
{
	GLCall(glUniform3i(GetUniformLocation(uniformName), value.x, value.y, value.z));
}

void Shader::SetUniform4i(const std::string& uniformName, const glm::ivec4& value)
{
	GLCall(glUniform4i(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
}

void Shader::SetUniform1u(const std::string& uniformName, unsigned value)
{
	GLCall(glUniform1ui(GetUniformLocation(uniformName), value));
}

void Shader::SetUniform2u(const std::string& uniformName, const glm::uvec2& value)
{
	GLCall(glUniform2ui(GetUniformLocation(uniformName), value.x, value.y));
}

void Shader::SetUniform3u(const std::string& uniformName, const glm::uvec3& value)
{
	GLCall(glUniform3ui(GetUniformLocation(uniformName), value.x, value.y, value.z));
}

void Shader::SetUniform4u(const std::string& uniformName, const glm::uvec4& value)
{
	GLCall(glUniform4ui(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
}

void Shader::SetUniformMat2f(const std::string& uniformName, const glm::mat2& value)
{
	GLCall(glUniformMatrix2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat2x3f(const std::string& uniformName, const glm::mat2x3& value)
{
	GLCall(glUniformMatrix2x3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat2x4f(const std::string& uniformName, const glm::mat2x4& value)
{
	GLCall(glUniformMatrix2x4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat3x2f(const std::string& uniformName, const glm::mat3x2& value)
{
	GLCall(glUniformMatrix3x2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat3f(const std::string& uniformName, const glm::mat3& value)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat3x4f(const std::string& uniformName, const glm::mat3x4& value)
{
	GLCall(glUniformMatrix3x4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat4x2f(const std::string& uniformName, const glm::mat4x2& value)
{
	GLCall(glUniformMatrix4x2fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat4x3f(const std::string& uniformName, const glm::mat4x3& value)
{
	GLCall(glUniformMatrix4x3fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

void Shader::SetUniformMat4f(const std::string& uniformName, const glm::mat4& value)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]));
}

unsigned Shader::CreateShader(const std::string& vertexShaderSourceCode, const std::string& fragmentShaderSourceCode)
{
	GLCall(unsigned programID = glCreateProgram());

	unsigned vertexShaderID = CompileShader(vertexShaderSourceCode, GL_VERTEX_SHADER);
	unsigned fragmentShaderID = CompileShader(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);

	GLCall(glAttachShader(programID, vertexShaderID));
	GLCall(glAttachShader(programID, fragmentShaderID));
	GLCall(glLinkProgram(programID));

	int success;
	GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &success));

	if (!success)
	{
		int lengthOfMessage;

		GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &lengthOfMessage));

		char* infoLog = new char[(size_t)lengthOfMessage];

		GLCall(glGetProgramInfoLog(programID, lengthOfMessage, &lengthOfMessage, infoLog));

		std::cout << infoLog << std::endl;

		delete[] infoLog;
	}

	GLCall(glDeleteShader(vertexShaderID));
	GLCall(glDeleteShader(fragmentShaderID));

	return programID;
}

unsigned Shader::CompileShader(const std::string& sourceCode, unsigned shaderType)
{
	const char* charShaderSource = sourceCode.c_str();

	GLCall(unsigned shaderID = glCreateShader(shaderType));
	GLCall(glShaderSource(shaderID, 1, &charShaderSource, nullptr));
	GLCall(glCompileShader(shaderID));

	int success;

	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		int lengthOfMessage;
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lengthOfMessage));
		char* infoLog = new char[(size_t)lengthOfMessage];

		GLCall(glGetShaderInfoLog(shaderID, lengthOfMessage, &lengthOfMessage, infoLog));
		std::cout << infoLog << std::endl;
		delete[] infoLog;

		return 0;
	}

	return shaderID;
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];
	GLCall(int location = glGetUniformLocation(m_RendererID, uniformName.c_str()));
	m_UniformLocationCache[uniformName] = location;
	return location;
}

std::string Shader::ReadShaderFile(const std::string& filepath)
{
	std::ifstream fileBuffer(filepath);
	std::stringstream strStream;
	strStream << "";
	std::string line;
	while (getline(fileBuffer, line))
		strStream << line << '\n';
	return strStream.str();
}
