#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class VertexBuffer;

enum class PrimitiveShape
{
	Cube
};

class MeshComponent : public Component
{
public:
	constexpr static const char* TYPE = "MeshComponent";

	void SetPrimitiveShape(PrimitiveShape shape);

	std::shared_ptr<VertexBuffer> GetVertexBuffer() const;

	void Update(Entity* parent, float deltaTime) override;
	
private:
	std::vector<float> triangleVertices;
	std::shared_ptr<VertexBuffer> vertexBuffer;
};
