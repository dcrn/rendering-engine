#include "Mesh.h"

#include <glbinding/gl/enum.h>
#include <glm/common.hpp>
#include <glm/common.hpp>
#include <iosfwd>
#include <iosfwd>
#include <vector>
#include <vector>

using namespace gl;

Mesh::Mesh():
	vertexBuffer(GL_ARRAY_BUFFER),
	indexBuffer(GL_ELEMENT_ARRAY_BUFFER)
{
}

void Mesh::SetVertices(const std::vector<glm::vec3> &vertices)
{
	vertexBuffer.SetData<glm::vec3, float>(GL_FLOAT, vertices);
}

void Mesh::SetIndices(const std::vector<GLushort> &indices)
{
	indexBuffer.SetData<GLushort, GLushort>(GL_UNSIGNED_SHORT, indices);
}

const Buffer& Mesh::GetVertexBuffer() const
{
	return vertexBuffer;
}

const Buffer& Mesh::GetIndexBuffer() const
{
	return indexBuffer;
}
