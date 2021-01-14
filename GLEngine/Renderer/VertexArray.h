#pragma once
#include <glad/glad.h>
#include <vector>

#include "VertexBuffer.h"

struct VertexBufferElement
{
	unsigned int size;
	unsigned int normalized;

	VertexBufferElement(unsigned int s, unsigned int n) noexcept
		:size{s}, normalized{n}
	{}

	VertexBufferElement(VertexBufferElement&& other) noexcept
		:size{std::move(other.size)}, normalized{std::move(other.normalized)}
	{}

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
			case(GL_FLOAT):
			{
				return 4;
				break;
			}
			default:
			{
				return 4;
				break;
			}
		}
	}
};
/*
Vertex array describes the layout for the VertexBuffer

When using this vertex array you should first describe the layout 
and then add the vertex buffer
*/
class VertexArray 
{
	std::vector<VertexBufferElement> elements;
	
	unsigned int type;
	unsigned int type_size;

	unsigned int Stride = 0;
	unsigned int id;

	std::vector<unsigned int> offsets;

public:
	VertexArray(unsigned int type) noexcept;
	~VertexArray() noexcept;

	//this is adding to the layout description
	void add_layout_element(VertexBufferElement&& el);
	
	//this will construct the actual vertex buffer with the with the layout in the elements vector
	void compile_layout();

	//bind the VAO
	void bind();
};