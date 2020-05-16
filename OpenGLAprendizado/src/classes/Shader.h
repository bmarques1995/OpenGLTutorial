#pragma once

#include <unordered_map>
#include <glm\glm.hpp>

struct ShaderProgramSource 
{
	std::string VertexSourceCode;
	std::string FragmentSourceCode;
};

class Shader 
{
private:
	std::string m_VertexShaderFilepath;
	std::string m_FragmentShaderFilepath;
	unsigned m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(std::string vertexFilepath, std::string fragmentFilepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& uniformName, float value);
	void SetUniform2f(const std::string& uniformName, const glm::vec2& value);
	void SetUniform3f(const std::string& uniformName, const glm::vec3& value);
	void SetUniform4f(const std::string& uniformName, const glm::vec4& value);
	
	void SetUniform1i(const std::string& uniformName, int value);
	void SetUniform2i(const std::string& uniformName, const glm::ivec2& value);
	void SetUniform3i(const std::string& uniformName, const glm::ivec3& value);
	void SetUniform4i(const std::string& uniformName, const glm::ivec4& value);
	
	void SetUniform1u(const std::string& uniformName, unsigned value);
	void SetUniform2u(const std::string& uniformName, const glm::uvec2& value);
	void SetUniform3u(const std::string& uniformName, const glm::uvec3& value);
	void SetUniform4u(const std::string& uniformName, const glm::uvec4& value);
	
	void SetUniformMat2f(const std::string& uniformName, const glm::mat2& value);
	void SetUniformMat2x3f(const std::string& uniformName, const glm::mat2x3& value);
	void SetUniformMat2x4f(const std::string& uniformName, const glm::mat2x4& value);
	
	void SetUniformMat3x2f(const std::string& uniformName, const glm::mat3x2& value);
	void SetUniformMat3f(const std::string& uniformName, const glm::mat3& value);
	void SetUniformMat3x4f(const std::string& uniformName, const glm::mat3x4& value);
	
	void SetUniformMat4x2f(const std::string& uniformName, const glm::mat4x2& value);
	void SetUniformMat4x3f(const std::string& uniformName, const glm::mat4x3& value);
	void SetUniformMat4f(const std::string& uniformName, const glm::mat4& value);

private:

	unsigned CreateShader(const std::string& vertexShaderSourceCode, const std::string& fragmentShaderSourceCode);
	unsigned CompileShader(const std::string& sourceCode, unsigned shaderType);
	int GetUniformLocation(const std::string& uniformName);
	std::string ReadShaderFile(const std::string& filepath);
};