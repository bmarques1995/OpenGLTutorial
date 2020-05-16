#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ErrorHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "classes/VertexArray.h"
#include "classes/ElementBuffer.h"
#include "classes/Shader.h"
#include "classes/Renderer.h"

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
	glfwWindowHint(GLFW_SAMPLES, 16);

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

	glEnable(GL_MULTISAMPLE);


	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	int numberOfAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);

	glm::vec3 positions[] =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)
	};

	unsigned indices[] =
	{
		0, 1, 2
	};

	VertexArray vertexArray;
	VertexBufferLayout vertexBufferLayout;
	VertexBuffer vertexBuffer(positions, 3 * sizeof(glm::vec3));

	vertexBufferLayout.Push<float>(3);
	vertexBufferLayout.Push<float>(3);
	vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
	ElementBuffer elementBuffer(indices, 3);

	Shader shader("src/shaders/triangle.vertex.glsl", "src/shaders/triangle.fragment.glsl");
	shader.Bind();

	Renderer renderer;

	shader.Unbind();
	vertexArray.Unbind();
	vertexBuffer.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		renderer.Clear();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		
		shader.Bind();
		vertexArray.Bind();
		vertexBuffer.Bind();

		renderer.Draw(vertexArray, elementBuffer, shader);

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
	strStream << "";
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
		char* infoLog = new char[(size_t)lengthOfMessage];

		GLCall(glGetShaderInfoLog(shaderID, lengthOfMessage, &lengthOfMessage, infoLog));
		std::cout << infoLog << std::endl;
		delete[] infoLog;

		return 0;
	}

	return shaderID;
}