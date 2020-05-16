#pragma once

class ElementBuffer 
{
private:
	unsigned m_RendererID;
	unsigned m_Count;
public:
	ElementBuffer(unsigned* data, unsigned count);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned GetCount() const;
};