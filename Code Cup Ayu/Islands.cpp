#include "Islands.h"

Islands::Islands(Board* board) :
	board(board),
	islands()
{

}


void Islands::addIsland(std::pair<int, int> position)
{
	islands.push_back(position);
}


void Islands::executeMoveOnBoard(std::pair<int, int> beginPos, std::pair<int, int> endPos)
{
	// Check all islands to see which one changes
	for (Island island : islands)
	{
		for (std::pair<int, int> point : island.allPoints)
		{
			if (point == beginPos)
			{
				island.removePiece(beginPos);
				island.addPiece(endPos);
			}
		}
	}
}
/*
// In case a piece moved we need to make sure that all adjacent pieces are now of the same island.
void Islands::mergeIslands(std::pair<int, int> endpos)
{
}*/
