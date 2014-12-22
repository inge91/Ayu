#include "Islands.h"
#include "Island.h"

#include <iostream>

Islands::Islands(Board* board) :
	board(board),
	islands()
{

}


void Islands::addIsland(Piece* piece)
{
	islands.push_back(new Island(piece, this));
}


void Islands::addIsland(Island* island)
{
	islands.push_back(island);
}


void Islands::removeIsland(Island* island)
{
	for (unsigned int i = 0; i < islands.size(); i++)
	{
		if (islands.at(i) == island)
		{
			islands.erase(islands.begin() + i);
			delete island;
		}
	}
}


void Islands::printIslands()
{
	std::cout << "Number of islands: " << islands.size() << "\n";
	for (unsigned int i = 0; i < islands.size(); i++)
	{
		islands.at(i)->printIslandContents();
	}
}

int Islands::getNumberOfIslands()
{
	return islands.size();
}


std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Islands::getPossibleActions()
{
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> possibleActions;
	bool found_move = false;
	for (int i = 0; i < islands.size(); i++)
	{
		for (int j = 0; j < islands.at(i)->endpoints.size(); j++)
		{
			std::pair<int, int> beginPos;
			beginPos.first = islands.at(i)->endpoints.at(j)->x;
			beginPos.second = islands.at(i)->endpoints.at(j)->y;

			std::vector<std::pair<int, int>> possibleActionsIsland = islands.at(i)->getPossibleMoves(islands.at(i)->endpoints.at(j), board);
			for (int k = 0; k < possibleActionsIsland.size(); k++)
			{
				std::pair<int, int> endPos;
				endPos = possibleActionsIsland.at(k);
				possibleActions.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(beginPos, endPos));
			}
		}
	}
	return possibleActions;
}


