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
	Block(int id);
	int getId();
private:
	int id;
};

#endif