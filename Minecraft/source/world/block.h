#ifndef BLOCK_H
#define BLOCK_H

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
	Block(int id);
	int getId();
private:
	int m_id;
};

#endif