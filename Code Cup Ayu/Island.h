#ifndef ISLAND_H
#define ISLAND_H
#include "Piece.h"
class Board;
class Islands;
#include <vector>


struct Island
{
	// Each newly defined island consists of only one piece.
	// This means the piece is also an endpoint.
	Island(Piece* newIsland, Islands* islands) :
		allPoints(),
		endpoints(),
		islands(islands)
	{
		newIsland->isLandBelongingTo = this;
		allPoints.push_back(newIsland);
		endpoints.push_back(newIsland);
	}
	// All points of the island.
	std::vector<Piece*> allPoints;
	// These are the endpoints of the islands that can be moved around on the board.
	std::vector<Piece*> endpoints;

	void removePiece(Piece* p);
	void addPiece(Piece* p, Board* b);
	// Pieces that used to be endpieces need to be reevaluated and possibly be removed from this list.
	void reevaluatEndPiece(Piece* pieceToReevaluate, Board* b);

	void removeEndPoint(Piece* piece);
	bool isEndpoint(Piece* piece);
	std::vector<std::pair<int, int>> getPossibleMoves(Piece* piece, Board* b);

	void printIslandContents();

	std::vector<Piece*> pieceInIslandClosestToOtherPieces;

	// Not owned here
	Islands* islands;

};


#endif