#include "VertexBuffer.h"

#include <glbinding/gl41/gl.h>
#include <vector>

using namespace gl;

VertexBuffer::VertexBuffer()
{
	bufferId = 0;
}

VertexBuffer::~VertexBuffer()
{
	if (IsValid())
	{
		glDeleteBuffers(1, &bufferId);
	}
}

void VertexBuffer::Bind(gl::GLuint attributeId)
{
	glEnableVertexAttribArray(attributeId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(
		attributeId,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);
}

void VertexBuffer::Unbind(gl::GLuint attributeId)
{
	glDisableVertexAttribArray(attributeId);
}

void VertexBuffer::LoadTriangles(std::vector<float> triangles)
{
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, triangles.size(), triangles.data(), GL_STATIC_DRAW);

	triangleCount = triangles.size() / 3 / 3;
}

bool VertexBuffer::IsValid() const
{
	return bufferId != 0;
}

size_t VertexBuffer::GetTriangleCount() const
{
	return triangleCount;
}
