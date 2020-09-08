#include "block.h"

Block::Block() : m_id(0) {}

Block::Block(int id) : m_id(id) {}

int Block::getId()
{
	return m_id;
}