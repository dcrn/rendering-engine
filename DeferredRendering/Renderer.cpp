#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <glbinding/gl41/gl.h>
#include <glbinding/glbinding.h>
#include <glm/common.hpp>
#include <glm/common.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/component_wise.hpp>


#include "Entity.h"
#include "MeshComponent.h"
#include "ShaderLoader.h"
#include "TransformComponent.h"
#include "VertexBuffer.h"

using namespace gl;

Renderer::Renderer() :
	projectionMatrix(glm::mat4(1.0f)),
	viewMatrix(glm::mat4(1.0f)),
	viewFovDegrees(75.0f),
	viewNear(0.1f),
	viewFar(100.0f)
{
	viewMatrix = glm::lookAt(glm::vec3(5.0f), glm::vec3(0.0f), glm::vec3(0, 0, 1));
}

void Renderer::Init()
{
	glbinding::initialize(glfwGetProcAddress, false);

	const std::vector<GLuint> shaders = {
		ShaderLoader::CompileShader("simple.vert", GL_VERTEX_SHADER),
		ShaderLoader::CompileShader("simple.frag", GL_FRAGMENT_SHADER)
	};
	programId = ShaderLoader::LinkProgram(shaders);
	mvpUniformId = glGetUniformLocation(programId, "ModelViewProjection");
}

void Renderer::Resize(int width, int height)
{
	extentWidth = width;
	extentHeight = height;

	projectionMatrix = glm::perspective(
		glm::radians(viewFovDegrees),
		static_cast<float>(extentWidth) / static_cast<float>(extentHeight),
		viewNear,
		viewFar);
}

void Renderer::SetView(glm::vec3 position, glm::quat orientation)
{
	viewMatrix = glm::translate(glm::toMat4(orientation), position);
}

void Renderer::SetProjection(float fovDegrees, float near, float far)
{
	viewFovDegrees = fovDegrees;
	viewNear = near;
	viewFar = far;
	
	projectionMatrix = glm::perspective(
		glm::radians(viewFovDegrees),
		static_cast<float>(extentWidth) / static_cast<float>(extentHeight),
		viewNear,
		viewFar);
}

void Renderer::BeginDraw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glUseProgram(programId);
}

void Renderer::DrawEntity(std::shared_ptr<Entity> entity)
{
	auto transform = entity->GetComponent<TransformComponent>();
	glm::vec3 position = transform ? transform->GetPosition() : glm::vec3(0.0f);
	glm::vec3 scale = transform ? transform->GetScale() : glm::vec3(1.0f);
	glm::quat orientation = transform ? transform->GetOrientation() : glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 modelMatrix = glm::translate(glm::scale(glm::toMat4(orientation), scale), position);
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	if (auto mesh = entity->GetComponent<MeshComponent>())
	{
		auto vertexBuffer = mesh->GetVertexBuffer();
		if (vertexBuffer)
		{
			vertexBuffer->Bind(0);

			glUniformMatrix4fv(mvpUniformId, 1, GL_FALSE, &mvp[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertexBuffer->GetTriangleCount()));
			vertexBuffer->Unbind(0);
		}
	}
}

void Renderer::EndDraw()
{
}
