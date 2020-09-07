#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>
#include <unordered_map>

#include "../maths/vector_hash.h"
#include "block.h"

class World;

using ChunkData = std::unordered_map<glm::vec3, Block>;

class Chunk
{
public:
	Chunk(World &world, VectorXZ pos);

	void load();
	
	bool chunkOnFile();
	void saveToFile();

	bool blockExistsAt(int x, int y, int z);

	ChunkData getBlocks();
	Block getBlock(int x, int y, int z);

	glm::vec3 getPosition();

	bool loaded;
private:
	VectorXZ position;
	World* world;
	ChunkData blocks;
};

#endif