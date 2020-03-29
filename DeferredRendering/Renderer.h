#pragma once

#include <glbinding/gl/types.h>
#include <glm/ext/quaternion_float.hpp>
#include <glm/mat4x4.hpp>

class Entity;

class Renderer
{
public:
	Renderer();
	void Init();
	void Resize(int width, int height);
	void SetView(glm::vec3 position, glm::quat orientation);
	void SetProjection(float fovDegrees, float near, float far);
	void BeginDraw();
	void DrawEntity(std::shared_ptr<Entity> entity);
	void EndDraw();

private:
	int extentWidth = 0;
	int extentHeight = 0;

	gl::GLuint programId = 0;
	gl::GLint mvpUniformId = 0;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	float viewFovDegrees;
	float viewNear;
	float viewFar;
};
