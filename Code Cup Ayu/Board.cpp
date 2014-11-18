#include "Board.h"

#include "BreadthFirst.h"
#include <iostream>

Board::Board(BoardContent color):
islandsAI(this),
islandsOpponent(this)
{
	colorAI = color;
	if (colorAI == BLACK)
	{
		colorOpponent = WHITE;
	}
	else
	{
		colorOpponent = BLACK;
	}
	
	// Fill in the board with pieces in start position.
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			if ((x % 2) != 0 && ((y % 2) == 0))
			{
				Piece* piece = new Piece(x, y, WHITE);
				if (colorAI == WHITE)
				{
					
					islandsAI.addIsland(piece);
				}
				else
				{
					islandsOpponent.addIsland(piece);
					Island* s = piece->isLandBelongingTo;
				}
				board[x][y] = piece;
			}
			else if ((x % 2) == 0 && ((y % 2) != 0))
			{
				Piece* piece = new Piece(x, y, BLACK);
				if (colorAI == BLACK)
				{
					islandsAI.addIsland(piece);
				}
				else
				{
					islandsOpponent.addIsland(piece);
				}
				board[x][y] = piece;
			}
			else
			{
				board[x][y] = new Piece(x, y, NONE);
			}
		}
	}

	initializeDistances();
}


void Board::initializeDistances()
{
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			if (board[x][y]->color != NONE)
			{ 
				board[x][y]->closestPieces = BreadthFirst::CalculateClosestSameColoredPieces(board[x][y], this, true);
				board[x][y]->isLandBelongingTo->setClosestPoints(board[x][y]);
			}
		}
	}
}


std::vector<Piece*> Board::getNeighbourPieces(Piece* p)
{
	std::vector<Piece*> neighbours;

	int x = p->x;
	int y = p->y;

	if (x > 0)
	{
		neighbours.push_back(board[x - 1][y]); 
	}
	if (x < 10)
	{
		neighbours.push_back(board[x + 1][y]);
	}
	if (y > 0)
	{
		neighbours.push_back(board[x][y - 1]);
	}
	if (y < 10)
	{
		neighbours.push_back(board[x][y + 1]);
	}

	return neighbours;
}

std::vector<std::pair<int, int>> Board::getEmptyNeighbourPositions(Piece* p)
{

	std::vector<std::pair<int, int>> emptyneighbours;

	int x = p->x;
	int y = p->y;

	if (x > 0 && board[x - 1][y]->color == NONE)
	{
		emptyneighbours.push_back(std::pair<int, int>(x - 1, y));
	}
	if (x < 10 && board[x + 1][y]->color == NONE)
	{
		emptyneighbours.push_back(std::pair<int, int>(x + 1, y));
	}
	if (y > 0 && board[x][y - 1]->color == NONE)
	{
		emptyneighbours.push_back(std::pair<int, int>(x , y - 1));
	}
	if (y < 10 && board[x][y + 1]->color == NONE)
	{
		emptyneighbours.push_back(std::pair<int, int>(x, y + 1));
	}

	return emptyneighbours;
}

// Structuur maken voor elke "tree" die gecreeerd wordt (kan ook een cirkel bevatten!)
// Alle mogelijke zetten vinden in een beurt ( dit zijn uiteindes van de tree structuur, dus knopen die maar een andere naast zich hebben van die kleur)
		// Alle mogelijke zetten is eerst kijken naar alle stenen die verplaatst kunnen worden, van elk van de eilandjes
		// En dan kijken waar geldig is om heen te zetten (kijk even in de regels)
// Een heuristiek maken welke zet het best gemaakt kan worden. (minmax?)
// een werkelijke zet doen op het bord( implementatie in Board)

// Maak een struct met een EndPoints vector waar je elke keer dat er een nieuw stuk wordt toegevoegd berekend of dit nieuwe stuk een endpoint is. 
// Je moet dan ook van de andere endpoints even checken of het nog eindpoints zijn hierna (door 4 plekken er omheen te kijken)


std::string Board::indexToBoardPosition(int x, int y)
{
	// Use ascii code to determine the letter belonging to the x index (65 is 'A')
	char horizontalPos = 65 + x;

	// The y is just a single increment from the given index
	std::string verticalPos = std::to_string(y+1);
	return  horizontalPos + verticalPos;
}


std::pair<int, int> Board::boardPositionToIndex(std::string boardPosition)
{
	// A possible board position : B3, so the first charac
	int x = boardPosition.c_str()[0] - 65;
	int y = std::stoi(boardPosition.substr(1, boardPosition.length())) - 1;
	return std::pair<int, int>(x, y);
}


void Board::stdPrintBoard()
{
	// Prints a representation of the current board.
	// Be aware that the y is printed upside down 
	for (int y = 10; y >= 0; y--)
	{
		for (int x = 0; x < 11; x++)
		{
			if (board[x][y]->color == NONE)
			{
				std::cout << ".";
			}
			else
			{
				switch (board[x][y]->color)
				{
				default:
				case BLACK:
					std::cout << "x";
					break;
				case WHITE:
					std::cout << "o";
					break;
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


void Board::errPrintBoard()
{
	// Prints a representation of the current board.
	// Be aware that the y is printed upside down 
	for (int y = 10; y >= 0; y--)
	{
		for (int x = 0; x < 11; x++)
		{
			if (board[x][y]->color == NONE)
			{
				std::cerr << ".";
			}
			else
			{
				switch (board[x][y]->color)
				{
				default:
				case BLACK:
					std::cerr << "x";
					break;
				case WHITE:
					std::cerr << "o";
					break;
				}
			}
		}
		std::cerr << "\n";
	}
	std::cerr << "\n";
}


void Board::executeMoveOnBoard(std::string move)
{
	std::regex rgx("(\\w\\d+)-(\\w\\d+)");
	std::smatch match;
	std::regex_search(move, match, rgx);

	// Extract the beginning and end position of the move on the board.
	std::pair<int, int> beginPos = boardPositionToIndex(match[1]);
	std::pair<int, int> endPos = boardPositionToIndex(match[2]);
	executeMoveOnBoard(beginPos, endPos);
}


void Board::executeMoveOnBoard(std::pair<int, int> beginPos, std::pair<int, int> endPos)
{
	Piece* pieceToMove = board[beginPos.first][beginPos.second];
	Piece* endPositionOfPiece = board[endPos.first][endPos.second];

	// Check if the begin position is not empty and the end position is.
	if (pieceToMove->color == NONE || endPositionOfPiece->color != NONE)
	{
		fprintf(stderr, "ERROR in Board::executeMoveOnBoard: beginning position was empty or endposition was not empty.");
		exit(0);
	}
	else
	{
		// Move the piece to the new location on the board (also update the inner position of the piece)
		board[beginPos.first][beginPos.second] = endPositionOfPiece;
		board[endPos.first][endPos.second] = pieceToMove;
		pieceToMove->x = endPos.first;
		pieceToMove->y = endPos.second;
		endPositionOfPiece->x = beginPos.first;
		endPositionOfPiece->y = beginPos.second;

		// Update closest pieces
		pieceToMove->closestPieces = BreadthFirst::CalculateClosestSameColoredPieces(pieceToMove, this, true);

		// Remove piece from current island and add to next island
		Island* islandOfMovedPiece = pieceToMove->isLandBelongingTo;
	
		// All surrounding pieces of the same colour at the new position should be merged into 
		// the same island as the newly moved piece.
		std::vector<Piece*> neighBourPieces = getNeighbourPieces(pieceToMove);
		for (unsigned int i = 0; i < neighBourPieces.size(); i++)
		{
			if (neighBourPieces.at(i)->color != NONE && neighBourPieces.at(i)->color == pieceToMove->color)
			{
				Island* neighbourPieceIsland = neighBourPieces.at(i)->isLandBelongingTo;
				if (neighbourPieceIsland == islandOfMovedPiece)
				{
					continue;
				}

				std::vector<Piece*> islandPieces = neighbourPieceIsland->allPoints;

				for (unsigned int j = 0; j < islandPieces.size(); j++)
				{
					islandPieces.at(j)->closestPieces = BreadthFirst::CalculateClosestSameColoredPieces(islandPieces.at(j), this, true);
					islandOfMovedPiece->addPiece(islandPieces.at(j), this);
				}

				// Remove the islands that have now been merged together.
				if (pieceToMove->color == colorAI)
				{
					islandsAI.removeIsland(neighbourPieceIsland);
				}
				else
				{
					islandsOpponent.removeIsland(neighbourPieceIsland);
				}
			}
		}
	}
	//islandsAI.printIslands();
}


void Board::calculateAndExecuteMoveOnBoard()
{
	std::pair<int, int> begin;
	std::pair<int, int> end;
	islandsAI.calculateBestMove(begin, end);
	std::string beginString = indexToBoardPosition(begin.first, begin.second);
	std::string endString = indexToBoardPosition(end.first, end.second);
	std::string move = beginString + "-" + endString + "\n";
	std::cout << move;
	executeMoveOnBoard(begin, end);
}

