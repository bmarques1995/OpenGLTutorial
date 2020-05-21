#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray 
{
private:
	unsigned m_VertexID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);
};