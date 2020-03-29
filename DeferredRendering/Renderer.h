#pragma once
#include <glbinding/gl/types.h>
#include <glm/mat4x4.hpp>

class Renderer
{
public:
	Renderer();
	void Init();
	void Resize(int width, int height);
	void Draw();

private:
	int extentWidth = 0;
	int extentHeight = 0;
	
	gl::GLuint programId = 0;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};

