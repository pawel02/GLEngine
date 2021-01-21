#pragma once
#include <vector>
#include <memory>

class IndexBuffer
{
	unsigned int m_id;

	unsigned int count;
public:
	IndexBuffer();
	IndexBuffer(unsigned int count, const void* indices) noexcept;
	~IndexBuffer() noexcept;

	//in case you dont want to supply data at construction
	void sub_data(unsigned int count, const void* indices);

	void bind();
	inline const unsigned int& getCount() const { return count; }
};

