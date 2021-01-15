#pragma once

class VertexBuffer
{
	unsigned int id;
	unsigned int count;

public:
	VertexBuffer(unsigned int count, const void* data) noexcept;
	~VertexBuffer() noexcept;

	const unsigned int& getCount() const { return count; }

	void bind();
};