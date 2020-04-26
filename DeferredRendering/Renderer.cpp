#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <glbinding/gl41/gl.h>
#include <glbinding/glbinding.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Entity.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "ShaderLoader.h"
#include "TransformComponent.h"

using namespace gl;

Renderer::Renderer() :
	projectionMatrix(glm::mat4(1.0f)),
	viewMatrix(glm::mat4(1.0f)),
	viewFovDegrees(75.0f),
	viewNear(0.1f),
	viewFar(100.0f)
{
	glbinding::initialize(glfwGetProcAddress, false);

	const std::vector<GLuint> shaders = {
		ShaderLoader::CompileShader("simple.vert", GL_VERTEX_SHADER),
		ShaderLoader::CompileShader("simple.frag", GL_FRAGMENT_SHADER)
	};
	programId = ShaderLoader::LinkProgram(shaders);
	uniformIdMVP = glGetUniformLocation(programId, "ModelViewProjection");
	attribIdVertexPos = glGetAttribLocation(programId, "VertexPosition");
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
	// TODO: Use quat for camera roll instead of just direction
	const glm::vec3 lookDir = glm::vec3(orientation.x, orientation.y, orientation.z);
	viewMatrix = glm::lookAt(position, position + lookDir, glm::vec3(0, 0, 1));
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
	const auto transform = entity->GetComponent<TransformComponent>();
	const glm::vec3 position = transform ? transform->GetPosition() : glm::vec3(0.0f);
	const glm::vec3 scale = transform ? transform->GetScale() : glm::vec3(1.0f);
	const glm::quat orientation = transform ? transform->GetOrientation() : glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	const glm::mat4 modelRotation = glm::toMat4(orientation);
	const glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), scale);
	const glm::mat4 modelTranslation = glm::translate(glm::mat4(1.0f), position);
	const glm::mat4 modelMatrix = modelTranslation * modelRotation * modelScale;

	const glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	if (auto meshComponent = entity->GetComponent<MeshComponent>())
	{
		if (auto mesh = meshComponent->GetMesh())
		{
			glUniformMatrix4fv(uniformIdMVP, 1, GL_FALSE, &mvp[0][0]);
			DrawMesh(mesh);
		}
	}
}

void Renderer::DrawMesh(const std::shared_ptr<Mesh>& mesh)
{
	const Buffer& vertexBuffer = mesh->GetVertexBuffer();
	const Buffer& indexBuffer = mesh->GetIndexBuffer();
	
	glEnableVertexAttribArray(attribIdVertexPos);
	glBindBuffer(vertexBuffer.GetBufferType(), vertexBuffer.GetId());
	glVertexAttribPointer(
		attribIdVertexPos,
		vertexBuffer.GetValueCount(),
		vertexBuffer.GetValueType(),
		GL_FALSE,
		0,
		nullptr);

	glBindBuffer(indexBuffer.GetBufferType(), indexBuffer.GetId());

	glDrawElements(
		GL_TRIANGLES, 
		indexBuffer.GetItemCount(), 
		indexBuffer.GetValueType(), 
		nullptr);

	glBindBuffer(indexBuffer.GetBufferType(), 0);
	glBindBuffer(vertexBuffer.GetBufferType(), 0);
	glDisableVertexAttribArray(attribIdVertexPos);
}

void Renderer::EndDraw()
{
}
