#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int count, const void* data) noexcept
	:count{count}
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() noexcept
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
