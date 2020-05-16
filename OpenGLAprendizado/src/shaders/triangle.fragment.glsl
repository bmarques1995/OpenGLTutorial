#version 330 core

out vec4 FragColor;
in vec3 fragmentColor;

void main()
{
	FragColor = vec4(fragmentColor.r, fragmentColor.g, fragmentColor.b, 1.0f);
}