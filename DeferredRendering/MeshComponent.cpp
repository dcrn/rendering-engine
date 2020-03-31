#include "MeshComponent.h"

#include "Mesh.h"

void MeshComponent::SetPrimitiveShape(PrimitiveShape shape)
{
	mesh = nullptr;
	
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

std::shared_ptr<Mesh> MeshComponent::GetMesh() const
{
	return mesh;
}

void MeshComponent::Update(Entity* parent, float deltaTime)
{
	if (!mesh)
	{
		mesh = std::make_shared<Mesh>();
		mesh->SetVertices(vertices);
		mesh->SetIndices(indices);
	}
}
