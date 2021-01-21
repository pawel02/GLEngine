#pragma once
#include "../Renderer/Renderer.h"
#include <array>

struct Vec2
{
	float x;
	float y;
};

struct Vec3
{
	float x;
	float y;
	float z;
};

struct Vertex
{
	Vec3 Pos;
	Vec2 TexCoords;
	float TexID;
};

template<size_t max_size>
class Quad
{
	const size_t MaxVertexCount = max_size * 4;
	const size_t MaxIndexCount = max_size * 6;

	std::array<Vertex, max_size> vertices;
	uint32_t indices[max_size * 6];

	uint32_t currOffset = 0;


	//all of the buffers
	VertexBuffer VBO;
	IndexBuffer EBO;
	VertexArray VAO;

	Buffers buffers;

public:
	Quad() 
		:VBO{ sizeof(Vertex) * MaxVertexCount },
		VAO{ GL_FLOAT }, 
		buffers{VAO, EBO, VBO}
	{
		//setup the index buffer
		uint32_t offset = 0;
		for (size_t i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		EBO.sub_data(MaxIndexCount, indices);

		VAO.add_layout_element({ sizeof(Vertex::Pos) / sizeof(float), GL_FALSE });

		VAO.add_layout_element({ sizeof(Vertex::TexCoords) / sizeof(float), GL_FALSE });
		
		VAO.add_layout_element({ 1, GL_FALSE });

		VAO.compile_layout();
	}

	void AddQuad(float offsetX, float offsetY, float size, float texID) 
	{
		//setup all the vertices
		vertices[currOffset].Pos = { offsetX , offsetY, 0 };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, 0 };
		vertices[currOffset].TexCoords = { 0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, 0 };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, 0 };
		vertices[currOffset].TexCoords = { 1.0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		VBO.sub_data(currOffset * sizeof(Vertex), vertices.data());
	}

	Buffers& get_buffers() { return buffers; }
};