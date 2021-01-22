#pragma once
#include "../util/Primitives.h"
#pragma once
#include "../Renderer/Renderer.h"
#include <array>
#include "../util/Primitives.h"

struct VBVA
{
	VertexBuffer& VBO;
	VertexArray& VAO;
};

template<size_t max_size>
class Cube
{
	const size_t MaxVertexCount = max_size * 6 * 6;

	std::array<Vertex, max_size * 6 * 6> vertices;

	uint32_t currOffset = 0;


	//all of the buffers
	VertexBuffer VBO;
	VertexArray VAO;

	VBVA buffers;
public:
	Cube()
		:VBO{ sizeof(Vertex) * MaxVertexCount },
		VAO{ GL_FLOAT },
		buffers{VBO, VAO}
	{
		VAO.add_layout_element({ sizeof(Vertex::Pos) / sizeof(float), GL_FALSE });

		VAO.add_layout_element({ sizeof(Vertex::TexCoords) / sizeof(float), GL_FALSE });

		VAO.add_layout_element({ 1, GL_FALSE });

		VAO.compile_layout();
	}

	void AddCube(float offsetX, float offsetY, float offsetZ, float size, float texID)
	{
		//front face
		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		//left face
		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		//back face
		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ};
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 1.0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ};
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		//right face
		vertices[currOffset].Pos = { offsetX + size , offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		//up face
		vertices[currOffset].Pos = { offsetX , offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX, offsetY + size, offsetZ};
		vertices[currOffset].TexCoords = { 0.0, 0.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size};
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX, offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 0.0, 0.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ };
		vertices[currOffset].TexCoords = { 0.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY + size, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		//bottom face
		vertices[currOffset].Pos = { offsetX , offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0.0, 0.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0.0, 0.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ };
		vertices[currOffset].TexCoords = { 0.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		vertices[currOffset].Pos = { offsetX + size, offsetY, offsetZ + size };
		vertices[currOffset].TexCoords = { 1.0, 1.0 };
		vertices[currOffset].TexID = texID;
		currOffset++;

		VBO.sub_data(currOffset * sizeof(Vertex), vertices.data());
	}

	VBVA& get_buffers() { return buffers; }
};