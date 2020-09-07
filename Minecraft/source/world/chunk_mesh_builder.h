#ifndef CHUNK_MESH_BUILDER_H
#define CHUNK_MESH_BUILDER_H

#include "chunk.h"
#include "mesh.h"

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder(Chunk& chunk, Mesh& mesh);
	void buildMesh();
	void tryAddFaceToMesh(const std::array<float, 12> &blockFace, const std::array<float, 8>& textureCoords,
		const glm::vec3 &blockPosition);
private:
	Chunk* chunk;
	Mesh* mesh;
};

#endif