#ifndef PIECE_H
#define PIECE_H

struct Island;
#include "Board.h"

struct Piece
{
	
	int x;
	int y;
	BoardContent color;
	Island*	isLandBelongingTo;
};


#endif