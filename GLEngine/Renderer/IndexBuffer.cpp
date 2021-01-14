#include "IndexBuffer.h"
#include <glad/glad.h>

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

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
