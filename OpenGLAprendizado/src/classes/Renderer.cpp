#include "Renderer.h"

#include <glad\glad.h>

void Renderer::Draw(const ElementBuffer& elementBuffer, unsigned vertexBuffer, unsigned vertexArray, const Shader& shader)
{
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	elementBuffer.Bind();
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindVertexArray(vertexArray);
	shader.Bind();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
