#pragma once

#include "Shader.h"
#include "ElementBuffer.h"

class Renderer 
{
public:
	void Draw(const ElementBuffer& elementBuffer, unsigned vertexBuffer, unsigned vertexArray, const Shader& shader);
	void Clear();
};