#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer()
	:count{0}
{
	glGenBuffers(1, &m_id);
}

IndexBuffer::IndexBuffer(unsigned int count, const void* indices) noexcept
	:count{count}
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

	//the indecies get moved to GPU memory so they can be deleted from CPU memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() noexcept
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::sub_data(unsigned int count, const void* indices)
{
	this->count = count;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
