#ifndef WORLD_H
#define WORLD_H

#include "chunk_manager.h"
#include "chunk.h"
#include "../renderer.h"
#include "../camera.h"
#include "texture_atlas.h"
#include "map_generator.h"

class World
{
public:
	World();
	glm::vec3 setSpawn(Camera player);
	std::pair<int,int> getCurrentChunk();
	bool updateCurrentChunk(Camera player);
	void loadSurroundingChunks(Camera player);
	void generateChunk(int x, int z, ChunkData &chunkData);
	void render(Renderer renderer, Camera player);
private:
	ChunkManager chunk_manager;
	TextureAtlas texture_atlas;
	MapGenerator map_generator;
	int currentChunkX;
	int currentChunkZ;
};

#endif