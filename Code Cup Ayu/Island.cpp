#include "Island.h"
#include "Board.h"
#include "BreadthFirst.h"
#include <iostream>

//QQQ can't deal yet with circular constructions...
void Island::addPiece(Piece* pieceToAdd, Board* b)
{
	if (!isPartOfIsland(pieceToAdd))
	{
		pieceToAdd->isLandBelongingTo = this;
		allPoints.push_back(pieceToAdd);

		std::vector<Piece*> neighbourPieces = b->getNeighbourPieces(pieceToAdd);
		int sameColoredNeighbourPieces = 0;
		for (unsigned int i = 0; i < neighbourPieces.size(); i++)
		{
			if (neighbourPieces.at(i)->color != NONE && neighbourPieces.at(i)->color == pieceToAdd->color)
			{
				sameColoredNeighbourPieces++;
			}
		}
		if (sameColoredNeighbourPieces <= 1)
		{
			endpoints.push_back(pieceToAdd);
		}
		
		piecesInIslandClosestToOtherIslands.clear();
		for (int i = 0; i < allPoints.size(); i++)
		{
			reevaluatEndPiece(allPoints.at(i), b);
			// QQQI give closestsamecoloredpieces knowledge about which island a piece belongs to so that closest pieces from this island are ignored
			allPoints.at(i)->closestPieces = BreadthFirst::CalculateClosestSameColoredPieces(allPoints.at(i), b, true);

			// If this piece is closer to another piece that is not part of this island than the current closest piece that is not part of this island
			// we change the piece that is closest to another piece.
			setClosestPoints(allPoints.at(i));
		}
	}
}

// Piece that used to be an endpoint but a new piece came between needs to be reevaluated if it still should belong to endpoints
void Island::reevaluatEndPiece(Piece* pieceToReevaluate, Board* b)
{

	std::vector<Piece*> neighbourPieces = b->getNeighbourPieces(pieceToReevaluate);
	int sameColoredNeighbourPieces = 0;
	for (unsigned int i = 0; i < neighbourPieces.size(); i++)
	{
		if (neighbourPieces.at(i)->color != NONE && neighbourPieces.at(i)->color == pieceToReevaluate->color)
		{
			sameColoredNeighbourPieces++;
		}
	}
	if (sameColoredNeighbourPieces > 1 && isEndpoint(pieceToReevaluate))
	{
		removeEndPoint(pieceToReevaluate);
	}
	else if (sameColoredNeighbourPieces <= 1 && !isEndpoint(pieceToReevaluate))
	{
		endpoints.push_back(pieceToReevaluate);
	}

}


void Island::setClosestPoints(Piece* p)
{

	// In case some closest points were already based on this Piece, they should be deleted
	// And we should start over.
	for (int i = 0; i < piecesInIslandClosestToOtherIslands.size(); i++)
	{
		if (piecesInIslandClosestToOtherIslands.at(i) == p)
		{
			piecesInIslandClosestToOtherIslands.erase(piecesInIslandClosestToOtherIslands.begin() + i);
		}
	}

	for (int i = 0; i < p->closestPieces.size(); i++)
	{
		if (p->closestPieces.at(i).first->isLandBelongingTo != this)
		{
			if (piecesInIslandClosestToOtherIslands.size() == 0 || 
				(p->closestPieces.at(i).second < piecesInIslandClosestToOtherIslands.at(0)->closestPieces.at(0).second
				&& p->closestPieces.at(i).second > 2))
			{
				piecesInIslandClosestToOtherIslands.clear();
				piecesInIslandClosestToOtherIslands.push_back(p);
				break;
			}
			else if ((p->closestPieces.at(i).second == piecesInIslandClosestToOtherIslands.at(0)->closestPieces.at(0).second
				&& p->closestPieces.at(i).second > 2))
			{
				piecesInIslandClosestToOtherIslands.push_back(p);
				break;
			}
		}
	}
}


void Island::removeEndPoint(Piece* piece)
{
	for (unsigned int i = 0; i < endpoints.size(); i++)
	{
		if (endpoints.at(i) == piece)
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

bool Island::isEndpoint(Piece* piece)
{
	for (unsigned int i = 0; i < endpoints.size(); i++)
	{
		if (endpoints.at(i) == piece)
		{
			return true;
		}
	}
	return false;
}


bool Island::isPartOfIsland(Piece* piece)
{
	for (unsigned int i = 0; i < allPoints.size(); i++)
	{
		if (allPoints.at(i) == piece)
		{
			return true;
		}
	}
	return false;
}

bool Island::pointBecameCloser(std::pair<Piece*, int> piece)
{
	for (unsigned int i = 0; i < piecesInIslandClosestToOtherIslands.size(); i++)
	{
		for (int j = 0; j < piecesInIslandClosestToOtherIslands.at(i)->closestPieces.size(); j++)
		{
			if (piecesInIslandClosestToOtherIslands.at(i)->closestPieces.at(j).first == piece.first 
				&& piecesInIslandClosestToOtherIslands.at(i)->closestPieces.at(j).second > piece.second)
			{
				return true;
			}
		}
	}
	return false;
}


std::vector<std::pair<int, int>> Island::getPossibleMoves(Piece* piece, Board* b)
{
	std::vector < std::pair<int, int>> possibleDestinations;
	//QQQ still doesnt deal with circular things
	if (isEndpoint(piece))
	{
		// In case the island is a singleton return all adjacent spaces that are empty as possible destinations.
		if (allPoints.size() == 1)
		{
			std::vector<Piece*> neighbourPoints = b->getNeighbourPieces(piece);
			for (int i = 0; i < neighbourPoints.size(); i++)
			{
				// Possible destinations should decrease the distance to current closest pieces
				if (neighbourPoints.at(i)->color == NONE)
				{
					neighbourPoints.at(i)->color = piece->color;
					std::vector<std::pair<Piece*, int>> closestPoints = BreadthFirst::CalculateClosestSameColoredPieces(neighbourPoints.at(i), b, false);
					neighbourPoints.at(i)->color = NONE;
					for (int j = 0; j < closestPoints.size(); j++)
					{
						if (pointBecameCloser(closestPoints.at(j)))
						{
							possibleDestinations.push_back(std::pair<int, int>(neighbourPoints.at(i)->x, neighbourPoints.at(i)->y));
							break;
						}
					}
				}				
			}

			return possibleDestinations;
		}
		// All adjacent empty spaces to the other points in the island are possible destinations
		else
		{
			// Loop over all pieces in Island that current piece could attach to
			for (unsigned int i = 0; i < piecesInIslandClosestToOtherIslands.size(); i++)
			{
				// Do not include the own endpoint
				if (piecesInIslandClosestToOtherIslands.at(i) == piece)
				{
					continue;
				}
				else
				{
					std::vector<Piece*> neighbourPoints = b->getNeighbourPieces(piecesInIslandClosestToOtherIslands.at(i));
					// Loop over all neighbour positions of the piece the piece could attach tos
					for (int j = 0; j < neighbourPoints.size(); j++)
					{
						// Possible destinations should decrease the distance to current closest pieces
						if (neighbourPoints.at(j)->color == NONE)
						{
							neighbourPoints.at(j)->color = piece->color;
							std::vector<std::pair<Piece*, int>> closestPoints = BreadthFirst::CalculateClosestSameColoredPieces(neighbourPoints.at(j), b, false);
							neighbourPoints.at(j)->color = NONE;
							// Loop over all closts points to check if there is a decrease in distance to closest pieces.
							for (int k = 0; k < closestPoints.size(); k++)
							{
						
								if (pointBecameCloser(closestPoints.at(k)))
								{
									possibleDestinations.push_back(std::pair<int, int>(neighbourPoints.at(j)->x, neighbourPoints.at(j)->y));
									break;
								}
							

							}
						}
					}
				}
			}
			return possibleDestinations;
		}
	}
	return possibleDestinations;
}

void Island::printIslandContents()
{
	for (unsigned int i = 0; i < allPoints.size(); i++)
	{
		std::cout << "(" << allPoints.at(i)->x << ", " << allPoints.at(i)->y << "), ";
		if (isEndpoint(allPoints.at(i)))
		{
			std::cout << "(end)";
		}

	}
	std::cout << "\n";
}