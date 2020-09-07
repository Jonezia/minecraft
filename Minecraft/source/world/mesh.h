#ifndef MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <array>

#include "vertex.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh();
	void addFace(const std::array<Vertex,4> &vertexData,
		const glm::vec3 &chunkPosition,
		const glm::vec3 &blockPosition);
	void bufferMesh();
private:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	int index;
	unsigned int VAO, VBO, EBO;
};

#endif
