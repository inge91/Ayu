#ifndef ISLANDS_H
#define ISLANDS_H

class Board;
struct Island;
struct Piece;

#include "Island.h"
#include <vector>

class Islands
{
public:
	Islands(Board* board);

	// The adding of islands by is only done at board construction. Each new island can consist of only one piece,
	// as this is the way the board isinitially set up.
	void addIsland(Piece* piece);
	void addIsland(Island* island);
	void removeIsland(Island* island);
	void printIslands();

	void calculateBestMove(std::pair<int, int> &beginPos, std::pair<int, int> &endPos);

public:
	std::vector<Island*> islands;

private:
	// Not owned here
	Board* board;
};


#endif