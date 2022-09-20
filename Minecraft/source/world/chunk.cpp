#include "chunk.h"

#include "world_constants.h"
#include "chunk_mesh_builder.h"
#include "world.h"

Chunk::Chunk(World& world, VectorXZ pos) : world(&world),
	position(glm::vec3(pos.x,0,pos.z)),
	loaded(false), hasMesh(false) {}

void Chunk::load()
{
	if (chunkOnFile()) {
	// load chunk from file
	}
	else {
		world->generateChunk(position.x, position.z, blocks);
	}

	loaded = true;
}

bool Chunk::chunkOnFile()
{
	return false;
}

void Chunk::saveToFile()
{
	blocks.clear();
	loaded = false;
	// todo: save to file
}

bool Chunk::blockExistsAt(int x, int y, int z)
{
	return this->blocks.find(glm::vec3(x,y,z)) != this->blocks.end();
}

bool Chunk::blockExistsAt(glm::vec3 pos)
{
	return this->blocks.find(pos) != this->blocks.end();
}

ChunkData &Chunk::getBlocks()
{
	return this->blocks;
}

BlockID Chunk::getBlockId(int x, int y, int z)
{
	if (!blockExistsAt(x, y, z)) {
		return BlockID::Air;
	}
	else {
		return this->blocks[glm::vec3(x, y, z)].getId();
	}
}

glm::vec3 &Chunk::getPosition()
{
	return position;
}

bool Chunk::makeMesh(Camera &player)
{	
	if (hasMesh) {
		return false;
	}
	else {
		// check if in camera frustrum
		ChunkMeshBuilder(*this, mesh).buildMesh();
		hasMesh = true;
		return true;
	}
}

void Chunk::drawChunk(Renderer &renderer, Camera &player)
{
	// if in view
	renderer.drawChunk(mesh, player.GetViewMatrix());
}