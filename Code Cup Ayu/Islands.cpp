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


void Islands::calculateBestMove(std::pair<int, int> &beginPos, std::pair<int, int> &endPos)
{
	bool found_move = false;
	for (int i = 0; i < islands.size(); i++)
	{
		for (int j = 0; j < islands.at(i)->endpoints.size(); j++)
		{
			beginPos.first = islands.at(i)->endpoints.at(j)->x;
			beginPos.second = islands.at(i)->endpoints.at(j)->y;

			std::vector<std::pair<int, int>> destinations = islands.at(i)->getPossibleMoves(islands.at(i)->endpoints.at(j), board);
			if (destinations.size() > 0)
			{
				endPos.first = destinations.at(0).first;
				endPos.second = destinations.at(0).second;
				found_move = true;
				break;
			}
		}
		if (found_move)
		{
			break;
		}
	}
}


