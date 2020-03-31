#include "Buffer.h"

#include <glbinding/gl41/gl.h>

using namespace gl;

Buffer::Buffer(gl::GLenum bufferType) :
	bufferId(0),
	bufferType(bufferType),
	itemCount(0),
	valueCount(0),
	valueType()
{
}

Buffer::~Buffer()
{
	if (bufferId != 0)
	{
		glDeleteBuffers(1, &bufferId);
	}
}

void Buffer::LoadData(const void* data, size_t size)
{
	if (bufferId == 0)
	{
		glGenBuffers(1, &bufferId);
	}

	glBindBuffer(bufferType, bufferId);
	glBufferData(bufferType, size, data, GL_STATIC_DRAW);
}

bool Buffer::IsValid() const
{
	return bufferId != 0;
}

GLuint Buffer::GetId() const
{
	return bufferId;
}

GLenum Buffer::GetBufferType() const
{
	return bufferType;
}

GLsizei Buffer::GetItemCount() const
{
	return itemCount;
}

GLsizei Buffer::GetValueCount() const
{
	return valueCount;
}

GLenum Buffer::GetValueType() const
{
	return valueType;
}
