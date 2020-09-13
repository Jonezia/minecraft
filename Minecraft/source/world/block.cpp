#include "block.h"

Block::Block() : m_id(BlockID::Air) {}

Block::Block(BlockID id) : m_id(id) {}

BlockID Block::getId()
{
	return m_id;
}