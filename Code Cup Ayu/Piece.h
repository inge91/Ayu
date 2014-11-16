#ifndef PIECE_H
#define PIECE_H


enum BoardContent;
struct Island;
#include <vector>


struct Piece
{
	Piece(int x, int y, BoardContent color) :
		x(x),
		y(y),
		color(color)
	{
	}
	int x;
	int y;
	BoardContent color;
	Island*	isLandBelongingTo;
	std::vector<std::pair<Piece*, int>> closestPieces;
};


#endif