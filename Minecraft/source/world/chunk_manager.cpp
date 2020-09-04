#include "chunk_manager.h"

void ChunkManager::clear()
{
	this->chunks.clear();
}

void ChunkManager::addChunk(VectorXZ pos, Chunk chunk)
{
	this->chunks.insert({pos,chunk });
}

void ChunkManager::addChunk(int x, int z, Chunk chunk)
{
	this->chunks.insert({ VectorXZ(x,z),chunk });
}