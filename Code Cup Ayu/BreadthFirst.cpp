#include "BreadthFirst.h"

#include "Board.h"
#include "Piece.h"
#include <vector>


// QQQI you need to calculate this for both our and opponents pieces so we know where we should add our build priority towards
// (between pieces that the opponent would like to connect
std::vector<std::pair<Piece*, int>> BreadthFirst::CalculateClosestSameColoredPieces(Piece* piece, Board* b, bool ignoreConnectedPieces)
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
	while (!solutionFound && expandedPaths.size() != 0)
	{
		// Expand all nodes 
		int currentExpandedPathsSize = expandedPaths.size();
		// In case the solution is found continue expanding nodes but
		for (int i = 0; i < currentExpandedPathsSize; i++)
		{
			std::vector<Piece*> path = expandedPaths.at(i);
			std::vector<Piece*> neighbours = b->getNeighbourPieces(path.at(path.size() - 1));

			for (int j = 0; j < neighbours.size(); j++)
			{
				std::vector<Piece*> path = expandedPaths.at(i);
				// In case this neighbour was already visited or it a part of the same island as the piece we are looking closest pieces for
				// go further with the next neighbour
				if (pieceInVector(neighbours.at(j), visitedNodes)
					|| (piece->isLandBelongingTo != NULL && piece->isLandBelongingTo->isPartOfIsland(neighbours.at(j))))
				{
					continue;
				}

				if (neighbours.at(j)->color == NONE || neighbours.at(j)->color == piece->color)
				{
					visitedNodes.push_back(neighbours.at(j));
					path.push_back(neighbours.at(j));
					if (neighbours.at(j)->color == piece->color)
					{
						if (!ignoreConnectedPieces || (ignoreConnectedPieces && path.size() > 2))
						{
							solutionFound = true;
							expandedPaths.push_back(std::vector<Piece*>(path));
						}
					}
					else
					{
						expandedPaths.push_back(std::vector<Piece*>(path));
						visitedNodes.push_back(neighbours.at(j));
					}
				}
			}
		}
		// Remove the first elements
		expandedPaths.erase(expandedPaths.begin(), expandedPaths.begin() + currentExpandedPathsSize);
	}

	if (solutionFound)
	{
		// Each expanded path that ends up on a piece is a same distance
		// We only need to check if it not yet added to the cloest pieces.
		for (int i = 0; i < expandedPaths.size(); i++)
		{
			Piece* pathEndPiece = expandedPaths.at(i).at(expandedPaths.at(i).size() - 1);
			if (pathEndPiece->color != NONE)
			{
				closestPieces.push_back(std::pair<Piece*, int>(pathEndPiece, expandedPaths.at(i).size()));
			}
		}
	}

	return closestPieces;
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