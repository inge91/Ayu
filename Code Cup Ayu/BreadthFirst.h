#ifndef BREADTHFIRST_H
#define BREADTHFIRST_H


class Board;
struct Piece;

#include <vector>


class BreadthFirst
{
public:
	static std::vector<std::pair<Piece*, int>> CalculateClosestSameColoredPieces(Piece* piece, Board* b, bool ignoreConnectedPieces);
	static bool pieceInVector(Piece* piece, std::vector<Piece*> pieces);

};


#endif
