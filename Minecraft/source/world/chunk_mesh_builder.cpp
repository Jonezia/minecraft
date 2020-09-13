#include "chunk_mesh_builder.h"

#include <array>
#include "vertex.h"
#include "texture_atlas.h"

namespace {
	const std::array<float, 12> topFace{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, };
	const std::array<float, 12> frontFace{0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,};
	const std::array<float, 12> backFace{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,};
	const std::array<float, 12> leftFace{0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,};
	const std::array<float, 12> rightFace{1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,};
	const std::array<float, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };
}

ChunkMeshBuilder::ChunkMeshBuilder(Chunk& chunk, Mesh& mesh) :
	m_chunk(&chunk), m_mesh(&mesh) {}

void ChunkMeshBuilder::buildMesh()
{
	// todo: replace with actual texCoords
	std::array<float, 8> defaultTexCoords = { 0, 0, 0, 1, 1, 1, 1, 0 };
	auto& blocks = m_chunk->getBlocks();
	for (auto itr = blocks.begin(); itr != blocks.end();) {
		glm::vec3 position = itr->first;
		Block block = itr->second;
		TexUVCoords UVCoords = TextureAtlas::getTextures(block.getId());

		tryAddFaceToMesh(topFace, UVCoords.topTexCoords, position);
		tryAddFaceToMesh(frontFace, UVCoords.sideTexCoords, position);
		tryAddFaceToMesh(backFace, UVCoords.sideTexCoords, position);
		tryAddFaceToMesh(leftFace, UVCoords.sideTexCoords, position);
		tryAddFaceToMesh(rightFace, UVCoords.sideTexCoords, position);
		tryAddFaceToMesh(bottomFace, UVCoords.bottomTexCoords, position);
		
		itr++;
	}
	m_mesh->bufferMesh();
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::array<float, 12>& blockFace, const std::array<float, 8>& texCoords,
	const glm::vec3& blockPosition)
{
	std::array<Vertex, 4> faceVertices;
	for (unsigned int i = 0; i < 4; i++) {
		faceVertices[i] = Vertex(glm::vec3(blockFace[3*i], blockFace[3*i + 1], blockFace[3*i + 2]),
			glm::vec2(texCoords[2*i], texCoords[2*i + 1]));
	}
	m_mesh->addFace(faceVertices, m_chunk->getPosition(), blockPosition);
}