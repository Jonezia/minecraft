#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>
#include <unordered_map>

#include "../maths/vector_hash.h"
#include "block.h"
#include "../camera.h"
#include "../renderer.h"
#include "mesh.h"
#include "block_id.h"

class World;

using ChunkData = std::unordered_map<glm::vec3, Block>;

class Chunk
{
public:
	Chunk() = default;
	Chunk(World &world, VectorXZ pos);

	void load();
	
	bool chunkOnFile();
	void saveToFile();

	bool blockExistsAt(int x, int y, int z);

	ChunkData &getBlocks();
	BlockID getBlockId(int x, int y, int z);

	glm::vec3 &getPosition();

	bool makeMesh(Camera &player);

	void drawChunk(Renderer &renderer, Camera &player);

	bool loaded;
	bool hasMesh;
private:
	glm::vec3 position;
	World* world;
	ChunkData blocks;
	Mesh mesh;
};

#endif