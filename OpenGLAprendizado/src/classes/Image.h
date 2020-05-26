#pragma once

#include <glad\glad.h>
#include <string>

#define IMAGE_JPG 0x0001u
#define IMAGE_PNG 0x0002u
#define IMAGE_BMP 0x0003u

class Image 
{
private:
	unsigned m_Width;
	unsigned m_Height;
	unsigned m_BitsPerPixel;
	unsigned char* m_ImageBuffer;
public:
	Image(std::string filepath);
	~Image();

	unsigned GetWidth() const;
	unsigned GetHeight() const;
	unsigned char* GetImageBuffer() const;
	unsigned CalculateFormat();
	int CalculateInternalFormat();
};