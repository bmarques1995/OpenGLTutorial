#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

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

	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.0f, 0.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ProcessInput(window);

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
