#include "Island.h"

void Island::removePiece(std::pair<int, int> pos)
{
	for (int i = 0; i < allPoints.size(); i ++)
	{
		if (allPoints.at(i) == pos)
		{
			allPoints.erase(allPoints.begin() + i);
			break;
		}
		if (i == allPoints.size() - 1)
		{
			fprintf(stderr, "ERROR in Island::removePiece: position does not occur in all points");
		}
	}

	for (int i = 0; i < endpoints.size(); i++)
	{
		if (endpoints.at(i) == pos)
		{
			endpoints.erase(endpoints.begin() + i);
			break;
		}
		if (i == endpoints.size() - 1)
		{
			fprintf(stderr, "ERROR in Island::removePiece: position does not occur in end points");
		}
	}
}

void Island::addPiece(std::pair<int, int> pos)
{
	allPoints.push_back(pos);
	// allPoints is an endpiece in case it only has a single neighbour with the same color
}
