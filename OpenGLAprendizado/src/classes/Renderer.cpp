#include "Renderer.h"

#include <glad\glad.h>

void Renderer::Draw(const ElementBuffer& elementBuffer, const VertexArray& vertexArray, const Shader& shader)
{
	elementBuffer.Bind();
	vertexArray.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, elementBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
