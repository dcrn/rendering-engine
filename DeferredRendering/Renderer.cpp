#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <glbinding/gl41/gl.h>
#include <glbinding/glbinding.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"

using namespace gl;

Renderer::Renderer()
{
	projectionMatrix = glm::identity<glm::mat4>();
	viewMatrix = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}

void Renderer::Init()
{
	glbinding::initialize(glfwGetProcAddress, false);

	const std::vector<GLuint> shaders = {
		ShaderLoader::CompileShader("simple.vert", GL_VERTEX_SHADER),
		ShaderLoader::CompileShader("simple.frag", GL_FRAGMENT_SHADER)
	};
	programId = ShaderLoader::LinkProgram(shaders);
}

void Renderer::Resize(int width, int height)
{
	extentWidth = width;
	extentHeight = height;

	projectionMatrix = glm::perspective(
		glm::radians(75.0f),
		static_cast<float>(extentWidth) / static_cast<float>(extentHeight),
		0.1f,
		100.0f);
}

void Renderer::Draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programId);

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

	glm::mat4 mvp = projectionMatrix * viewMatrix;
	GLuint mvpUniformId = glGetUniformLocation(programId, "ModelViewProjection");
	glUniformMatrix4fv(mvpUniformId, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
