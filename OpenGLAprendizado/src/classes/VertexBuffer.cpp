#include "VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned size)
{
	glGenBuffers(1, &m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
