#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "ElementBuffer.h"

class Renderer 
{
public:
	void Draw(const VertexArray& vertexArray, const ElementBuffer& elementBuffer, const Shader& shader);
	void Clear();
};