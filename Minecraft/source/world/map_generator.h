#pragma once

#include "chunk.h"
#include "../SimplexNoise.h"

class MapGenerator
{
public:
	MapGenerator(int seed);

	void generateChunk(int x, int z, ChunkData &blocks);

private:
	int seed;
	SimplexNoise simplexNoise;
};