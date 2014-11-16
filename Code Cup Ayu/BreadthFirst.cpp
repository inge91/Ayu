#include "BreadthFirst.h"

#include "Board.h"
#include "Piece.h"
#include <vector>


// QQQI you need to calculate this for both our and opponents pieces so we know where we should add our build priority towards
// (between pieces that the opponent would like to connect
std::vector<std::pair<Piece*, int>> BreadthFirst::CalculateClosestSameColoredPieces(Piece* piece, Board* b)
{
	std::vector<std::pair<Piece*, int>> closestPieces;

	std::vector<Piece*> firstNode;
	firstNode.push_back(piece);

	std::vector<Piece*> visitedNodes;
	visitedNodes.push_back(piece);

	std::vector < std::vector<Piece*> > expandedPaths;
	expandedPaths.push_back(firstNode);

	bool solutionFound = false;

	// While not empty and not yet found closest nodes)
	while (!solutionFound || expandedPaths.size() == 0)
	{
		// Expand all nodes 
		int currentExpandedPathsSize = expandedPaths.size();
		// In case the solution is found continue expanding nodes but
		for (int i = 0; i < currentExpandedPathsSize; i++)
		{
			std::vector<Piece*> path =  expandedPaths.at(i);
			std::vector<Piece*> neighbours = b->getNeighbourPieces(path.at(path.size()));

			for (int i = 0; i < neighbours.size(); i++)
			{
				if (pieceInVector(neighbours.at(i), visitedNodes))
				{
					continue;
				}

				if (neighbours.at(i) == NULL || neighbours.at(i)->color == piece->color)
				{
					path.push_back(neighbours.at(i));
					// QQI well there's your problem
					expandedPaths.push_back(path);
					visitedNodes.push_back(neighbours.at(i));

					if (neighbours.at(i)->color == piece->color)
					{
						solutionFound = true;
					}
				}
			}
			// Remove the first elements
			expandedPaths.erase(expandedPaths.begin(), expandedPaths.begin() + currentExpandedPathsSize);
		}
	}

	if (solutionFound)
	{
		// Each expanded path that ends up on a piece is a same distance
		// We only need to check if it not yet added to the cloest pieces.
		for (int i = 0; i < expandedPaths.size(); i++)
		{
			Piece* pathEndPiece = expandedPaths.at(i).at(expandedPaths.at(i).size());
			if (pathEndPiece != NULL)
			{
				closestPieces.push_back(std::pair<Piece*, int>(pathEndPiece, expandedPaths.at(i).size()));
			}
		}
	}
	else
	{
		// Something went very wrong
		exit(0);
	}
}


bool BreadthFirst::pieceInVector(Piece* piece, std::vector<Piece*> pieces)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (piece == pieces.at(i))
		{
			return true;
		}
	}
	return false;
}