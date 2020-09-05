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
	void render(Renderer renderer, Camera player);
private:
	ChunkManager chunk_manager;
};

#endif