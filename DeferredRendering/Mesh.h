#pragma once

#include <glm/vec3.hpp>
#include <glbinding/gl/types.h>
#include <vector>

#include "Buffer.h"

class Mesh
{
public:
	Mesh();
	
	void SetVertices(const std::vector<glm::vec3>& vertices);
	void SetIndices(const std::vector<gl::GLushort>& indices);

	const Buffer& GetVertexBuffer() const;
	const Buffer& GetIndexBuffer() const;

private:
	Buffer vertexBuffer;
	Buffer indexBuffer;
};
