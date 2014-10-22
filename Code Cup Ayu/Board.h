#ifndef BOARD_H
#define BOARD_H

#include "Islands.h"

#include <string>
enum BoardContent
{
	EMPTY,
	WHITE,
	BLACK
};

class Board
{
public:
	Board(BoardContent color);

	std::vector<BoardContent> getNeighbourPieces(std::pair<int, int> position);

private:
	int boardSize;
	BoardContent board[11][11];
	BoardContent colorOpponent;
	// Should be allocated
	Islands islandsOpponent;

	BoardContent colorAI;
	// Should be allocated
	Islands islandsAI;
	
	

public:
	void executeMoveOnBoard(std::string move);

private:
	std::string indexToBoardPosition(int x, int y);
	std::pair<int, int> boardPositionToIndex(std::string boardPosition);

	void stdPrintBoard();
	void errPrintBoard();
};


#endif