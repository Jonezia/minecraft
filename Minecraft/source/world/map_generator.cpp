#include "map_generator.h"
#include "world_constants.h"
#include <algorithm>

MapGenerator::MapGenerator(int seed) : seed(seed) {}

void MapGenerator::generateChunk(int x, int z, ChunkData &blocks) {

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			int height =
				// base structure
				std::max(int(8 * (simplexNoise.fractal(9, x * CHUNK_SIZE + i, z * CHUNK_SIZE + j) + 1)), 1)
				// detail
				+ std::max(int(3 * (simplexNoise.fractal(6, x * CHUNK_SIZE + i, z * CHUNK_SIZE + j) + 1)), 0)
				// mountains
				+ std::max(int(32 * simplexNoise.fractal(8, x * CHUNK_SIZE + i, z * CHUNK_SIZE + j)), 0);
			for (int k = 0; k < height; k++) {
				Block block(BlockID::Grass);
				blocks.emplace(glm::vec3(i, k, j), std::move(block));
			}
		}
	}

}
