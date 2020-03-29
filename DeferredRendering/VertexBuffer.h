#pragma once

#include <glbinding/gl/types.h>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind(gl::GLuint attributeId);
	void Unbind(gl::GLuint attributeId);
	void LoadTriangles(std::vector<gl::GLfloat> triangles);
	bool IsValid() const;
	size_t GetTriangleCount() const;
	
private:
	gl::GLuint bufferId;
	size_t triangleCount;
};
