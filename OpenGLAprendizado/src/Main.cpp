#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

#include "classes/Renderer.h"
#include "classes/Shader.h"
#include "classes/ElementBuffer.h"
#include "classes/VertexArray.h"
#include "classes/VertexBuffer.h"
#include "classes/VertexBufferLayout.h"

#include "./vendor/stb_image/stb_image.h"
#include "classes/Image.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

struct Point
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture;
};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 128);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif 

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_MULTISAMPLE);
    
    //ativa a transparência

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    
    Shader shader("src/shaders/triangle.vertex.glsl", "src/shaders/triangle.fragment.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Point vertices[] = {
        // positions                    // colors
        {glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },  
        {glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },  
        {glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
        {glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) }  
    };

    unsigned indices[] =
    {
        0, 1, 2,
        1, 2, 3
    };

    VertexBuffer vertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.Push<float>(3);
    vertexBufferLayout.Push<float>(4);
    vertexBufferLayout.Push<float>(2);

    ElementBuffer elementBuffer(indices, sizeof(indices)/ sizeof(unsigned));

    VertexArray vertexArray;

    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
   
    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    shader.Unbind();
    vertexArray.Unbind();

#pragma region Texture

    unsigned texture1;
    unsigned texture2;

    Image* image1 = new Image("src/textures/wall.png");
    Image* image2 = new Image("src/textures/awesomeface.png");

    glGenTextures(1, &texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexImage2D(GL_TEXTURE_2D, 0, image1->CalculateInternalFormat(), image1->GetWidth(), image1->GetHeight(), 0, image1->CalculateFormat(), GL_UNSIGNED_BYTE, image1->GetImageBuffer());
    glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, image2->CalculateInternalFormat(), image2->GetWidth(), image2->GetHeight(), 0, image2->CalculateFormat(), GL_UNSIGNED_BYTE, image2->GetImageBuffer());
    glGenerateMipmap(GL_TEXTURE_2D);

    shader.Bind();
    shader.SetUniform1u("u_Texture1", 0);
    shader.SetUniform1u("u_Texture2", 1);
    
    
    delete image2;
    delete image1;
#pragma endregion

    Renderer renderer;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        ProcessInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        renderer.Clear();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render the triangle
        renderer.Draw(elementBuffer, vertexArray, shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}