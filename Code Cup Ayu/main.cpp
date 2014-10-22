#include <iostream>
#include <string> 
#include "Board.h"


BoardContent getColor(std::string input)
{
	if (input.compare("Start"))
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


	if (!input.compare("Start"))
	{
		Board b = Board(BLACK);
		b.executeMoveOnBoard(input);
		// QQQ Execute own move
	}

	
	while (true)
	{
		std::getline(std::cin, input);
		if (input.compare("Quit"))
		{
			break;
		}
		else
		{
			b.executeMoveOnBoard(input);
			// QQQ Execute own move
		}
	}
}