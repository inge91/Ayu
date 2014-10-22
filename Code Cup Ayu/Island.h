#ifndef ISLAND_H
#define ISLAND_H

#include <vector>

struct Island
{
	// Each newly defined island consists of only one piece.
	// This means the piece is also an endpoint.
	Island(std::pair<int, int> newIsland):
		allPoints(),
		endpoints()
	{
		allPoints.push_back(newIsland);
		endpoints.push_back(newIsland);
	}
	// All points of the island.
	std::vector<std::pair<int, int>> allPoints;
	// These are the endpoints of the islands that can be moved around on the board.
	std::vector<std::pair<int, int>> endpoints;

	void removePiece(std::pair<int, int>);
	void addPiece(std::pair<int, int>);
};


#endif