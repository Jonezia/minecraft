#include "chunk.h"
#include "world_constants.h"

Chunk::Chunk(World& world, VectorXZ pos) : world(&world), position(pos) {}

void Chunk::load()
{
	if (chunkOnFile()) {
	// load chunk from file
	}
	else {
		// Temp: replace with generator class
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				Block block (1);
				blocks.emplace(glm::vec3(x,z,0), std::move(block));
			}
		}
		// end Temp
	}
}

bool Chunk::chunkOnFile()
{
	return false;
}

void Chunk::saveToFile()
{

}

bool Chunk::blockExistsAt(int x, int y, int z)
{
	return this->blocks.find(glm::vec3(x,y,z)) != this->blocks.end();
}

ChunkData Chunk::getBlocks()
{
	return this->blocks;
}

Block Chunk::getBlock(int x, int y, int z)
{
	if (!blockExistsAt(x, y, z)) {
		return 0;
	}
	else {
		return this->blocks[glm::vec3(x, y, z)].getId();
	}
}