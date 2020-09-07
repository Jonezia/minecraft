#include "chunk_manager.h"

ChunkManager::ChunkManager(World& world) : world(&world) {}

bool ChunkManager::loadChunk(int x, int z)
{
	if (!chunkLoaded(x, z))
	{
		getChunk(x, z).load();
		return true;
	}
	return false;
}

void ChunkManager::unloadChunk(int x, int z)
{
	getChunk(x, z).saveToFile();
	chunks.erase({ x,z });
}

bool ChunkManager::chunkExistsAt(int x, int z)
{
	return this->chunks.find({ x, z }) != this->chunks.end();
}

bool ChunkManager::chunkLoaded(int x, int z)
{
	if (!chunkExistsAt(x, z)) return false;
	return this->chunks[VectorXZ {x, z}].loaded;
}

ChunkMap ChunkManager::getChunks()
{
	return this->chunks;
}

Chunk ChunkManager::getChunk(int x, int z)
{
	VectorXZ key{ x,z };
	if (!chunkExistsAt(x, z)) {
		Chunk chunk{ *world, key };
		chunks.emplace(key, std::move(chunk));
	}
	return chunks[key];
}

bool ChunkManager::makeMesh(int x, int z, Camera &player)
{
	getChunk(x, z).makeMesh(player);
}

void ChunkManager::clear()
{
	this->chunks.clear();
}