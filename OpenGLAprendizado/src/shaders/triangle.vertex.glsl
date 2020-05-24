#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexture;

out vec4 fragmentColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
	fragmentColor = vec4(inColor.r, inColor.g, inColor.b, inColor.a);
	TexCoord = inTexture;
}