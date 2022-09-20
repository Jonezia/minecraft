#include "world.h"

#include "world_constants.h"

World::World() : texture_atlas(),
    chunk_manager(*this), map_generator(12345678) {}

glm::vec3 World::setSpawn(Camera player)
{
    // todo
    chunk_manager.loadChunk(0, 0);
    chunk_manager.makeMesh(0, 0, player);

    glm::vec3 spawnPos = { 0,0,0 };

    currentChunkX = spawnPos.x - 1;
    currentChunkZ = spawnPos.z - 1;

    player.setPosition(spawnPos);
    return spawnPos;
}

std::pair<int,int> World::getCurrentChunk() {
    std::pair<int, int> XZPos(currentChunkX, currentChunkZ);
    return XZPos;
}

bool World::updateCurrentChunk(Camera player)
{
    int chunkX = player.Position.x / CHUNK_SIZE;
    int chunkZ = player.Position.z / CHUNK_SIZE;
    if (chunkX != currentChunkX || chunkZ != currentChunkZ) {
        currentChunkX = chunkX;
        currentChunkZ = chunkZ;
        return true;
    }
    return false;
}

void World::loadSurroundingChunks(Camera player)
{
    if (!(updateCurrentChunk(player))) {
        return;
    }

    // todo: instead of looking through all chunks and deleting,
    // use direction of travel to only delete those that need to be deleted
    auto& chunkMap = chunk_manager.getChunks();
    for (auto itr = chunkMap.begin(); itr != chunkMap.end();) {
        Chunk &chunk = itr->second;

        int minX = currentChunkX - LOAD_DISTANCE;
        int minZ = currentChunkZ - LOAD_DISTANCE;
        int maxX = currentChunkX + LOAD_DISTANCE;
        int maxZ = currentChunkZ + LOAD_DISTANCE;

        auto location = chunk.getPosition();

        if (minX > location.x || minZ > location.z || maxZ < location.z ||
            maxX < location.x) {
            chunk.saveToFile();
            itr = chunkMap.erase(itr);
            continue;
        }

        itr++;
    }

    for (int i = -LOAD_DISTANCE; i < LOAD_DISTANCE + 1; i++) {
        for (int j = -LOAD_DISTANCE; j < LOAD_DISTANCE + 1; j++) {
            if (chunk_manager.loadChunk(currentChunkX + i, currentChunkZ + j))
            {
                chunk_manager.makeMesh(currentChunkX + i, currentChunkZ + j, player);
            }
        }
    }
}

void World::generateChunk(int x, int z, ChunkData &chunkData) {
        map_generator.generateChunk(x, z, chunkData);
}

void World::render(Renderer renderer, Camera player)
{
    auto& chunkMap = chunk_manager.getChunks();

    int cameraX = player.Position.x;
    int cameraZ = player.Position.z;

    int minX = (cameraX / CHUNK_SIZE) - RENDER_DISTANCE;
    int minZ = (cameraZ / CHUNK_SIZE) - RENDER_DISTANCE;
    int maxX = (cameraX / CHUNK_SIZE) + RENDER_DISTANCE;
    int maxZ = (cameraZ / CHUNK_SIZE) + RENDER_DISTANCE;

    for (auto itr = chunkMap.begin(); itr != chunkMap.end();) {
        Chunk &chunk = itr->second;

        auto location = chunk.getPosition();

        if (minX > location.x || minZ > location.z || maxZ < location.z ||
            maxX < location.x) {
            itr = chunkMap.erase(itr);
            continue;
        }
        else {
            chunk.drawChunk(renderer, player);
            itr++;
        }
    }
}