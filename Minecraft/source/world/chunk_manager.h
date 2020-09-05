#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <unordered_map>

#include "chunk.h"
#include "../maths/vector_hash.h"

class World;

using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class ChunkManager
{
public:
	ChunkManager(World &world);
	
	void loadChunk(int x, int z);
	void unloadChunk(int x, int z);
	
	bool chunkExistsAt(int x, int z);
	bool chunkLoaded(int x, int z);

	ChunkMap getChunks();
	Chunk getChunk(int x, int z);

	void clear();

private:
	ChunkMap chunks;
	World* world;
};

#endif