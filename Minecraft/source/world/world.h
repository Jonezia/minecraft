#ifndef WORLD_H
#define WORLD_H

#include "chunk_manager.h"

class World
{
public:
	World();
	~World();
private:
	ChunkManager chunk_manager;
};

#endif