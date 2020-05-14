#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ErrorHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
std::string readFile(std::string path);

unsigned CreateShader(std::string vertexShader, std::string fragmentShader);
unsigned CompileShader(std::string shader, unsigned shaderType);

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, u8"Olá GLAD!", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Janela falhou ao iniciar" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -2;

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glm::vec3 positions[] =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f,  0.5f, 0.0f)
	};

	std::string vertexShader = readFile("src/shaders/triangle.vertex.glsl");
	std::string fragmentShader = readFile("src/shaders/triangle.fragment.glsl");

	unsigned programID = CreateShader(vertexShader, fragmentShader);

	unsigned VertexBuffer;
	GLCall(glGenBuffers(1, &VertexBuffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	unsigned VertexArray;
	GLCall(glGenVertexArrays(1, &VertexArray));
	GLCall(glBindVertexArray(VertexArray));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.0f, 0.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		GLCall(glUseProgram(programID));
		GLCall(glBindVertexArray(VertexArray));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

std::string readFile(std::string path)
{
	std::ifstream fileBuffer(path);
	std::stringstream strStream;
	std::string line;
	while (getline(fileBuffer, line))
		strStream << line << '\n';
	return strStream.str();
}

unsigned CreateShader(std::string vertexShaderSource, std::string fragmentShaderSource)
{
	GLCall(unsigned programID = glCreateProgram());

	GLCall(unsigned vertexShaderID = CompileShader(vertexShaderSource, GL_VERTEX_SHADER));
	GLCall(unsigned fragmentShaderID = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER));

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

unsigned CompileShader(std::string shaderSource, unsigned shaderType)
{
	const char* charShaderSource = shaderSource.c_str();

	GLCall(unsigned shaderID = glCreateShader(shaderType));
	GLCall(glShaderSource(shaderID, 1, &charShaderSource, nullptr));
	GLCall(glCompileShader(shaderID));

	int success;

	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		int lengthOfMessage;

		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lengthOfMessage));

		char* infoLog = new char[(size_t) lengthOfMessage];

		GLCall(glGetShaderInfoLog(shaderID, lengthOfMessage, &lengthOfMessage, infoLog));

		std::cout << infoLog << std::endl;

		delete[] infoLog;
	}

	return shaderID;
}