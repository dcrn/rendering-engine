#include "Renderer.h"

#include <GLFW/glfw3.h>

#include <glbinding/gl41/gl.h>
#include <glbinding/glbinding.h>

using namespace gl;

void Renderer::Init()
{
	glbinding::initialize(glfwGetProcAddress, false);
}

void Renderer::Resize(int width, int height)
{
	extentWidth = width;
	extentHeight = height;
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	static const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);
	
	glDrawArrays(GL_TRIANGLES, 0, 3); 
	glDisableVertexAttribArray(0);
}
