#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <unordered_map>

#include "chunk.h"
#include "../maths/vector_hash.h"

class ChunkManager
{
public:
	ChunkManager() = default;
	void clear();
	void addChunk(VectorXZ pos, Chunk chunk);
	void addChunk(int x, int z, Chunk chunk);
private:
	std::unordered_map<VectorXZ, Chunk> chunks;
};

#endif