#include "Board.h"

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
				if (colorAI == WHITE)
				{
					islandsAI.addIsland(std::pair<int, int>(x, y));
				}
				else
				{
					islandsOpponent.addIsland(std::pair<int, int>(x, y));
				}
				board[x][y] = WHITE;
			}
			else if ((x % 2) == 0 && ((y % 2) != 0))
			{
				if (colorAI == BLACK)
				{
					islandsAI.addIsland(std::pair<int, int>(x, y));
				}
				else
				{
					islandsOpponent.addIsland(std::pair<int, int>(x, y));
				}
				board[x][y] = BLACK;
			}
			else
			{
				board[x][y] = EMPTY;
			}
		}
	}
}


std::vector<BoardContent> Board::getNeighbourPieces(std::pair<int, int> position)
{
	std::vector<BoardContent> neighbours;

	int x = position.first;
	int y = position.second;


	if (x > 0)
	{
		neighbours.push_back(board[x+1][y]); 
	}
	if (x < 10)
	{
		neighbours.push_back(board[x - 1][y]);
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
	std::string verticalPos = std::to_string(y++);
	return verticalPos + horizontalPos;
}


std::pair<int, int> Board::boardPositionToIndex(std::string boardPosition)
{
	// A possible board position : B3, so the first charac
	int x = boardPosition.c_str()[0] - 65;
	int y = boardPosition.c_str()[1] - 1;
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
			switch (board[x][y])
			{
				default:
				case EMPTY:
					std::cout << ".";
					break;
				case BLACK:
					std::cout << "x";
					break;
				case WHITE:
					std::cout << "o";
					break;
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
			switch (board[x][y])
			{
			default:
			case EMPTY:
				std::cerr << ".";
				break;
			case BLACK:
				std::cerr << "x";
				break;
			case WHITE:
				std::cerr << "o";
				break;
			}
		}
		std::cerr << "\n";
	}
	std::cerr << "\n";
}

void Board::executeMoveOnBoard(std::string move)
{
	std::pair<int, int> beginPos = boardPositionToIndex(move.substr(0, 2));
	std::pair<int, int> endPos = boardPositionToIndex(move.substr(3, 2));

	BoardContent beginColor = board[beginPos.first][beginPos.second];
	BoardContent endColor = board[endPos.first][endPos.second];
	if (beginColor == EMPTY || endColor != EMPTY)
	{
		fprintf(stderr, "ERROR in Board::executeMoveOnBoard: beginning position was empty or endposition was not empty.");
		exit(0);
	}
	else
	{
		// Move on the board
		board[beginPos.first][beginPos.second] = EMPTY;
		board[endPos.first][endPos.second] = beginColor;

		// Move in the islands.
		if (beginColor == colorAI)
		{

		}
		else
		{

		}

	}
}


