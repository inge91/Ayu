#include "Island.h"
#include "Board.h"
#include <iostream>

// It is not possible to remove pieces REMOVE THIS FUNCTION

void Island::removePiece(Piece* piece)
{
	for (unsigned int i = 0; i < allPoints.size(); i ++)
	{
		if (allPoints.at(i) == piece)
		{
			allPoints.erase(allPoints.begin() + i);
			break;
		}
		if (i == allPoints.size() - 1)
		{
			fprintf(stderr, "ERROR in Island::removePiece: position does not occur in all points");
		}
	}

	removeEndPoint(piece);
	piece->isLandBelongingTo = NULL;

	// In case this piece 

	
	if (allPoints.empty())
	{
		islands->removeIsland(this);
		delete this;
	}
}

//QQQ can't deal yet with circular constructions...
void Island::addPiece(Piece* pieceToAdd, Board* b)
{
	pieceToAdd->isLandBelongingTo = this;
	allPoints.push_back(pieceToAdd);

	std::vector<Piece*> neighbourPieces = b->getNeighbourPieces(pieceToAdd);
	int sameColoredNeighbourPieces = 0;
	for (unsigned int i = 0; i < neighbourPieces.size(); i++)
	{
		if (neighbourPieces.at(i) != NULL && neighbourPieces.at(i)->color == pieceToAdd->color)
		{
			sameColoredNeighbourPieces++;
		}
	}
	if (sameColoredNeighbourPieces <= 1)
	{
		endpoints.push_back(pieceToAdd);
	}

	// Reevalute 
	for (unsigned int i = 0; i < neighbourPieces.size(); i++)
	{
		if (neighbourPieces.at(i) != NULL && neighbourPieces.at(i)->color == pieceToAdd->color)
		{
			reevaluatEndPiece(neighbourPieces.at(i), b);
		}
	}
}

// Piece that used to be an endpoint but a new piece came between needs to be reevaluated if it still should belong to endpoints
void Island::reevaluatEndPiece(Piece* pieceToReevaluate, Board* b)
{
	if (isEndpoint(pieceToReevaluate))
	{
		std::vector<Piece*> neighbourPieces = b->getNeighbourPieces(pieceToReevaluate);
		int sameColoredNeighbourPieces = 0;
		for (unsigned int i = 0; i < neighbourPieces.size(); i++)
		{
			if (neighbourPieces.at(i) != NULL && neighbourPieces.at(i)->color == pieceToReevaluate->color)
			{
				sameColoredNeighbourPieces++;
			}
		}
		if (sameColoredNeighbourPieces > 1)
		{
			removeEndPoint(pieceToReevaluate);
		}
	}
}
\
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


std::vector<std::pair<int, int>> Island::getPossibleMoves(Piece* piece, Board* b)
{
	std::vector < std::pair<int, int>> possibleDestinations;
	//QQQ still doesnt deal with circular things
	if (isEndpoint(piece))
	{
		// In case the island is a singleton return all adjacent spaces that are empty as possible destinations.
		if (allPoints.size() == 1)
		{
			std::vector<std::pair<int, int>> neighbourPoints = b->getEmptyNeighbourPositions(piece);
			for (int i = 0; i < neighbourPoints.size(); i++)
			{
			
				possibleDestinations.push_back(std::pair<int, int>(neighbourPoints.at(i).first, neighbourPoints.at(i).second));
				
			}

			return possibleDestinations;
		}
		// All adjacent empty spaces to the other points in the island are possible destinations
		else
		{
			// QQI should also decrease distance to nearest other group, not increase it :( The distance between two pieces is the shortest path of adjacent empty points between them
			for (unsigned int i = 0; i < allPoints.size(); i++)
			{
				// Do not include the own endpoint
				if (allPoints.at(i) == piece)
				{
					continue;
				}
				else
				{
					std::vector<std::pair<int, int>> neighbourPoints = b->getEmptyNeighbourPositions(piece);
					for (int i = 0; i < neighbourPoints.size(); i++)
					{
						if (neighbourPoints.at(i).first != piece->x && neighbourPoints.at(i).second != piece->y)
						{
							possibleDestinations.push_back(std::pair<int, int>(neighbourPoints.at(i).first, neighbourPoints.at(i).second));
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