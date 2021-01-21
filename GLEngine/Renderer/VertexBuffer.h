#pragma once

class VertexBuffer
{
	unsigned int id;
	unsigned int count;

public:
	VertexBuffer(unsigned int count) noexcept;

	VertexBuffer(unsigned int count, const void* data) noexcept;
	~VertexBuffer() noexcept;

	void sub_data(unsigned int data_size, const void* data);

	const unsigned int& getCount() const { return count; }

	void bind();
};