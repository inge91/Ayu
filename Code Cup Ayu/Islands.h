#ifndef ISLANDS_H
#define ISLANDS_H

class Board;

#include "Island.h"
#include <vector>

class Islands
{
public:
	Islands(Board* board);
	std::vector<Island> islands;

public:
	// The adding of islands is only done at board construction. Each new island can consist of only one piece,
	// as this is the way the board isinitially set up.
	void addIsland(std::pair<int, int> position);
	void executeMoveOnBoard(std::pair<int, int> beginPos, std::pair<int, int> endPos);

private:
	// Not owned here
	Board* board;
};


#endif