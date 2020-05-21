#include "VertexArray.h"

#include <glad\glad.h>
#include <glm\glm.hpp>


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();

	const auto& elements = vertexBufferLayout.GetElements();
	unsigned offset = 0;

	for (size_t i = 0; i < elements.size(); i++)
	{
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, vertexBufferLayout.GetStride(), (const void *) offset);
		glEnableVertexAttribArray(i);
		offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
	}
	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void *) sizeof(glm::vec3));
	glEnableVertexAttribArray(1);*/
}
