#ifndef WORLD_H
#define WORLD_H

#include "chunk_manager.h"
#include "chunk.h"
#include "../renderer.h"
#include "../camera.h"

class World
{
public:
	World();
	glm::vec3 setSpawn(Camera player);
	bool updateCurrentChunk(Camera player);
	void loadSurroundingChunks(Camera player);
	void render(Renderer renderer, Camera player);
private:
	ChunkManager chunk_manager;
	int currentChunkX;
	int currentChunkZ;
};

#endif