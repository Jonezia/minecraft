#include "map_generator.h"
#include "world_constants.h"

MapGenerator::MapGenerator(int seed) : seed(seed) {}

void MapGenerator::generateChunk(int x, int z, ChunkData &blocks) {

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			int height =  64  * (simplexNoise.fractal(12, x * CHUNK_SIZE + i, z * CHUNK_SIZE + j) + 1) + 1;
			for (int k = 0; k < height; k++) {
				Block block(BlockID::Grass);
				blocks.emplace(glm::vec3(i, k, j), std::move(block));
			}
		}
	}

}
