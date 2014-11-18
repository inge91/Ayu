#ifndef BOARD_H
#define BOARD_H

struct Piece;
#include "Islands.h"

#include <regex>
#include <string>
#include <vector>
enum BoardContent
{
	WHITE,
	BLACK,
	NONE
};

class Board
{
public:
	Board(BoardContent color);

	void initializeDistances();

	std::vector<Piece*> getNeighbourPieces(Piece* p);
	std::vector<std::pair<int, int>> getEmptyNeighbourPositions(Piece* p);

	void stdPrintBoard();
	void errPrintBoard();

	void executeMoveOnBoard(std::string move);
	void executeMoveOnBoard(std::pair<int, int> beginPos, std::pair<int, int> endPos);
	void calculateAndExecuteMoveOnBoard();

private:
	std::string indexToBoardPosition(int x, int y);
	std::pair<int, int> boardPositionToIndex(std::string boardPosition);


private:
	int boardSize;
	// The board consists of pointers ot Pieces, or NULL in case
	// the position on the board is empty.
	Piece* board[11][11];
	BoardContent colorOpponent;
	// Should be allocated
	Islands islandsOpponent;

	BoardContent colorAI;
	// Should be allocated
	Islands islandsAI;

};


#endif