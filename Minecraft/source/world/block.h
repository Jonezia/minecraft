#ifndef BLOCK_H
#define BLOCK_H

#include "block_id.h"

//      2--------3
//     /|       /|
//    1--------4 |
//    | |      | |
//    | 6------|-7
//    |/       |/
//    5--------8

class Block
{
public:
	Block();
	Block(BlockID id);
	BlockID getId();
private:
	BlockID m_id;
};

#endif