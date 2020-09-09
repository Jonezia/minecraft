#include "world.h"

#include "world_constants.h"

World::World() : chunk_manager(*this) {}

glm::vec3 World::setSpawn(Camera player)
{
    // todo
    chunk_manager.loadChunk(0, 0);
    chunk_manager.makeMesh(0, 0, player);
    //chunk_manager.loadChunk(0, 1);
    //chunk_manager.makeMesh(0, 1, player);
    //chunk_manager.loadChunk(1, 0);
    //chunk_manager.makeMesh(1, 0, player);

    glm::vec3 spawnPos = { 0,0,0 };
    player.setPosition(spawnPos);
    updateCurrentChunk(player);
    return spawnPos;
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

    auto& chunkMap = chunk_manager.getChunks();
    for (auto itr = chunkMap.begin(); itr != chunkMap.end();) {
        Chunk &chunk = itr->second;

        int minX = currentChunkX - LOAD_DISTANCE;
        int minZ = currentChunkZ - LOAD_DISTANCE;
        int maxX = currentChunkX + LOAD_DISTANCE;
        int maxZ = currentChunkZ + LOAD_DISTANCE;

        auto location = chunk.getPosition();

        if (minX > location.x || minZ > location.y || maxZ < location.y ||
            maxX < location.x) {
            itr = chunkMap.erase(itr);
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

        if (minX > location.x || minZ > location.y || maxZ < location.y ||
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