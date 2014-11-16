#include <iostream>
#include <string> 
#include "Board.h"


BoardContent getColor(std::string input)
{
	if (input.compare("Start") == 0)
	{
		return WHITE;
	}
	else
	{
		return BLACK;
	}
}

int main()
{
	std::string input = "test string \n";
	std::getline(std::cin, input);

	Board b(getColor(input));
	// The opponent started the game so
	// the move has to be executed on the board.
	if (input.compare("Start") != 0)
	{
		b.executeMoveOnBoard(input);
		b.stdPrintBoard();
	}
	
	b.calculateAndExecuteMoveOnBoard();


	b.stdPrintBoard();
	while (true)
	{
		std::getline(std::cin, input);
		if (input.compare("Quit") == 0)
		{
			break;
		}
		else
		{
			b.executeMoveOnBoard(input);
			b.stdPrintBoard();
			b.calculateAndExecuteMoveOnBoard();
			b.stdPrintBoard();
		}
	}
}