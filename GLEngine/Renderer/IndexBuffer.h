#pragma once
#include <vector>
#include <memory>

class IndexBuffer
{
	unsigned int m_id;

	unsigned int count;
public:
	IndexBuffer(unsigned int count, const void* indices) noexcept;
	~IndexBuffer() noexcept;

	void bind();
	inline const unsigned int& getCount() const { return count; }
};

