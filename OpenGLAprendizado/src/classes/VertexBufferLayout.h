#pragma once
#include <vector>
#include <unordered_map>
#include <glad\glad.h>
#include "../ErrorHandler.h"

struct VertexBufferElement 
{
	unsigned count;
	unsigned type;
	unsigned char normalized;

	static unsigned GetSizeOfType(unsigned type) 
	{
		std::unordered_map<unsigned, unsigned> mapper;

		mapper[GL_FLOAT] = 4;
		mapper[GL_UNSIGNED_INT] = 4;
		mapper[GL_UNSIGNED_BYTE] = 1;

		if (mapper.find(type) == mapper.end())
		{
			ASSERT(false);
			return 0;

		}
		return mapper[type];
	}
};

class VertexBufferLayout 
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned m_Stride;
public:
	VertexBufferLayout();

	template<typename T> void Push(unsigned count);
	template<> void Push<float>(unsigned count);
	template<> void Push<unsigned>(unsigned count);
	template<> void Push<unsigned char>(unsigned count);

	unsigned GetStride() const;
	std::vector<VertexBufferElement> GetElements() const;
};

template<typename T>
inline void VertexBufferLayout::Push(unsigned count)
{
	static_assert(false);
}

template<>
inline void VertexBufferLayout::Push<float>(unsigned count)
{
	m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned>(unsigned count)
{
	m_Elements.push_back({count, GL_UNSIGNED_INT, GL_TRUE});
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned count)
{
	m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE});
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
