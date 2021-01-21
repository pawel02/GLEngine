#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int count) noexcept
	:count{count}
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, count, nullptr, GL_DYNAMIC_DRAW);
}

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

void VertexBuffer::sub_data(unsigned int data_size, const void* data)
{
	//setting the dynamic vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data);
}

void VertexBuffer::bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
