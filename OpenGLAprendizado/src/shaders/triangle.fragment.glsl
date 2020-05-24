#version 330 core

out vec4 FragColor;

in vec4 fragmentColor;
in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, TexCoord) * fragmentColor;
}