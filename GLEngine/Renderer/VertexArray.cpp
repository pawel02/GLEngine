#include "VertexArray.h"

VertexArray::VertexArray(unsigned int type) noexcept
	:type{type}, type_size {VertexBufferElement::GetSize(type)}, Stride{ 0 }
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

VertexArray::~VertexArray() noexcept
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::add_layout_element(VertexBufferElement&& el)
{
	offsets.emplace_back(Stride);
	elements.emplace_back(std::move(el));
	Stride += el.size * type_size;
}

void VertexArray::compile_layout()
{
	//make sure that this vertex array is bound
	bind();

	unsigned int i = 0;
	for (auto&& el : elements)
	{
		glVertexAttribPointer(i, el.size, type, el.normalized,
			Stride, (const void*)(offsets[i]));
		glEnableVertexAttribArray(i);
		i++;
	}
}

void VertexArray::bind()
{
	glBindVertexArray(id);
}
