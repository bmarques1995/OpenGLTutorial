#pragma once

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

class Renderer 
{
public:
	void Draw(const ElementBuffer& elementBuffer, const VertexArray& vertexArray, const Shader& shader);
	void Clear();
};