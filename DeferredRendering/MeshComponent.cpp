#include "MeshComponent.h"

#include "VertexBuffer.h"

void MeshComponent::SetPrimitiveShape(PrimitiveShape shape)
{
	vertexBuffer = nullptr;
	
	if (shape == PrimitiveShape::Cube)
	{
		vertices = {
			glm::vec3(-0.5, -0.5, -0.5),
			glm::vec3(0.5, -0.5, -0.5),
			glm::vec3(0.5, 0.5, -0.5),
			glm::vec3(-0.5, 0.5, -0.5),
			
			glm::vec3(-0.5, -0.5, 0.5),
			glm::vec3(0.5, -0.5, 0.5),
			glm::vec3(0.5, 0.5, 0.5),
			glm::vec3(-0.5, 0.5, 0.5)
		};

		indices = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			3, 0, 4,
			4, 7, 3,
			2, 1, 5,
			5, 6, 2,
			1, 0, 4,
			4, 5, 1,
			2, 3, 7,
			7, 6, 2
		};
	}
}

std::shared_ptr<VertexBuffer> MeshComponent::GetVertexBuffer() const
{
	return vertexBuffer;
}

void MeshComponent::Update(Entity* parent, float deltaTime)
{
	if (!vertexBuffer || !vertexBuffer->IsValid())
	{
		vertexBuffer = std::make_shared<VertexBuffer>();
		vertexBuffer->LoadVertices(vertices);
		vertexBuffer->LoadIndices(indices);
	}
}
