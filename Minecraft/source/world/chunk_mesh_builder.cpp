#include "chunk_mesh_builder.h"

#include <array>
#include "vertex.h"

namespace {
	const std::array<GLfloat, 12> frontFace{0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,};
	const std::array<GLfloat, 12> backFace{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,};
	const std::array<GLfloat, 12> leftFace{0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,};
	const std::array<GLfloat, 12> rightFace{1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,};
	const std::array<GLfloat, 12> topFace{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, };
	const std::array<GLfloat, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };
}

ChunkMeshBuilder::ChunkMeshBuilder(Chunk& chunk, Mesh& mesh) :
	chunk(&chunk), mesh(&mesh) {}

void ChunkMeshBuilder::buildMesh()
{
	// replace with actual texCoords
	std::array<float, 8> defaultTexCoords = { 0, 0, 0, 1, 1, 1, 1, 0 };
	for (std::pair<glm::vec3, Block> element : this->chunk->getBlocks) {
		glm::vec3 position = element.first;
		Block block = element.second;
		tryAddFaceToMesh(topFace, defaultTexCoords, position);
	}
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::array<float, 12>& blockFace, const std::array<float, 8>& texCoords,
	const glm::vec3& blockPosition)
{
	std::array<Vertex, 4> faceVertices;
	for (int i = 0; i < 4; i++) {
		faceVertices[i] = Vertex(glm::vec3(blockFace[i], blockFace[i + 1], blockFace[i + 2]),
			glm::vec2(texCoords[i], texCoords[i + 1]));
	}
	mesh->addFace(faceVertices, chunk->getPosition, blockPosition);
}