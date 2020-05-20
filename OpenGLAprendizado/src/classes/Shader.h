#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <glm\glm.hpp>

struct ShaderInitializer
{
	unsigned Type;
	std::string ShaderFilepath;
};


class Shader
{
private:
	unsigned m_ProgramID;
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

	void SetUniform1d(const std::string& uniformName, int value);
	void SetUniform2d(const std::string& uniformName, const glm::ivec2& value);
	void SetUniform3d(const std::string& uniformName, const glm::ivec3& value);
	void SetUniform4d(const std::string& uniformName, const glm::ivec4& value);

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

	std::string ReadFile(const std::string& filepath);
	int GetUniformLocation(const std::string& uniformName);
	unsigned CreateShader(std::vector<ShaderInitializer> shaderFilepath);
	unsigned CompileShader(std::string shaderSource, unsigned shaderType);
	std::string StringShaderType(unsigned shaderType);

};