#pragma once

#include <vector>
#include <string>

class Texture 
{
private:
	unsigned m_TextureID;
public:
	Texture();
	~Texture();

	void Bind() const;
	void Unbind() const;

	void SaveTexture(std::string textureFilepath) const;
};