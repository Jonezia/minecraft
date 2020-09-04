#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include <glm/glm.hpp>

#include "world_constants.h"

using chunkDataContainer = std::array<int, 3 * CHUNK_VOLUME>;

class Chunk
{
public:
	Chunk() = default;
	Chunk(chunkDataContainer chunkData);
private:
	chunkDataContainer chunk_data;
};

#endif