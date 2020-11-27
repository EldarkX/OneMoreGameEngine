
#include "Modules/RenderModule/VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, unsigned int* indices, unsigned int numIndices)
{
	//create vertex array
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//Create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(float), verts, GL_STATIC_DRAW);

	//Create indices buffer
	glGenBuffers(1, &mIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndicesBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

