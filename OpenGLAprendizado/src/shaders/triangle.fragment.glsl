#version 330 core

out vec4 FragColor;

in vec4 fragmentColor;
in vec2 TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
	vec4 colorTexture_1 = texture(u_Texture1, TexCoord);
	vec4 colorTexture_2 = texture(u_Texture2, TexCoord);
	FragColor = colorTexture_2;
}