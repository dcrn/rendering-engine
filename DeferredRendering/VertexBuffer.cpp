#include "VertexBuffer.h"

#include <glbinding/gl41/gl.h>
#include <vector>

using namespace gl;

VertexBuffer::VertexBuffer() :
	vertexBufferId(0),
	indexBufferId(0)
{
}

VertexBuffer::~VertexBuffer()
{
	if (vertexBufferId != 0)
	{
		glDeleteBuffers(1, &vertexBufferId);
	}
	if (indexBufferId != 0)
	{
		glDeleteBuffers(1, &indexBufferId);
	}
}

void VertexBuffer::LoadVertices(std::vector<glm::vec3> vertices)
{
	this->vertices = vertices;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::LoadIndices(std::vector<uint16_t> indices)
{
	this->indices = indices;
	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
}

bool VertexBuffer::IsValid() const
{
	return vertexBufferId != 0 && indexBufferId != 0;
}

GLuint VertexBuffer::GetVertexBufferId() const
{
	return vertexBufferId;
}

GLuint VertexBuffer::GetIndexBufferId() const
{
	return indexBufferId;
}

gl::GLsizei VertexBuffer::GetVertexCount() const
{
	return vertices.size();
}

gl::GLsizei VertexBuffer::GetIndexCount() const
{
	return indices.size();
}
