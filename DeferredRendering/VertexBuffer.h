#pragma once

#include <glbinding/gl/types.h>
#include <glm/vec3.hpp>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void LoadVertices(std::vector<glm::vec3> vertices);
	void LoadIndices(std::vector<uint16_t> indices);
	bool IsValid() const;
	gl::GLuint GetVertexBufferId() const;
	gl::GLuint GetIndexBufferId() const;
	gl::GLsizei GetVertexCount() const;
	gl::GLsizei GetIndexCount() const;

private:
	gl::GLuint vertexBufferId;
	gl::GLuint indexBufferId;

	std::vector<glm::vec3> vertices;
	std::vector<uint16_t> indices;
};
