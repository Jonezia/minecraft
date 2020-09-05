#include "block.h"

Block::Block(int id) : id(id) {}

int Block::getId()
{
	return this->id;
}