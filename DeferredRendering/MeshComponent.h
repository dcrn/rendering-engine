#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include "Component.h"

class Mesh;

enum class PrimitiveShape
{
	Cube
};

class MeshComponent : public Component
{
public:
	constexpr static const char* TYPE = "MeshComponent";

	void SetPrimitiveShape(PrimitiveShape shape);

	std::shared_ptr<Mesh> GetMesh() const;

	void Update(Entity* parent, float deltaTime) override;
	
private:
	std::shared_ptr<Mesh> mesh;
	std::vector<glm::vec3> vertices;
	std::vector<uint16_t> indices;
};
