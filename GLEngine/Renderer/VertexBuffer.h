#pragma once

class VertexBuffer
{
	unsigned int id;
public:
	VertexBuffer(unsigned int count, const void* data) noexcept;
	~VertexBuffer() noexcept;

	void bind();
};