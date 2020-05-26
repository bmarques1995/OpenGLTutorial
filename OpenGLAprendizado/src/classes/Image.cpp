#include "Image.h"
#include <stb_image/stb_image.h>
#include <glad\glad.h>

#include <unordered_map>
#include <iostream>

Image::Image(std::string filepath) : m_ImageBuffer(nullptr)
{
	int width, height, bitsPerPixel;
	stbi_set_flip_vertically_on_load(true);
	m_ImageBuffer = stbi_load(filepath.c_str(), &width, &height, &bitsPerPixel, 0);
	m_Width = width;
	m_Height = height;
	m_BitsPerPixel = bitsPerPixel;
}

Image::~Image()
{
	stbi_image_free(m_ImageBuffer);
}

unsigned Image::GetWidth() const
{
	return m_Width;
}

unsigned Image::GetHeight() const
{
	return m_Height;
}

unsigned char* Image::GetImageBuffer() const
{
	return m_ImageBuffer;
}

unsigned Image::CalculateFormat()
{
	std::unordered_map<unsigned, unsigned> format;
	format[3] = GL_RGB;
	format[4] = GL_RGBA;

	return format[m_BitsPerPixel];
}

int Image::CalculateInternalFormat()
{
	std::unordered_map<unsigned, unsigned> format;
	format[3] = GL_RGB;
	format[4] = GL_RGBA8;

	return format[m_BitsPerPixel];
}