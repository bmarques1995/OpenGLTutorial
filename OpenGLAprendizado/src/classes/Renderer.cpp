#include "Renderer.h"

#include "../ErrorHandler.h"

void Renderer::Draw(const VertexArray& vertexArray, const ElementBuffer& elementBuffer, const Shader& shader)
{
	shader.Bind();
	vertexArray.Bind();
	elementBuffer.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, elementBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
