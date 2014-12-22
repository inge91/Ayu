#include <iostream>
#include <string> 
#include <fstream>
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

	bool readFromFile = true;
	std::ifstream infile("moves.txt");
	std::string line;
	std::string input = "test string \n";
	if (readFromFile)
	{
		if (std::getline(infile, line))
		{
			std::regex rgx("(\\w\\d+)-(\\w\\d+)");
			std::smatch match;
			std::regex_search(line, match, rgx);

			input = match[0];
		}
		else
		{
			std::getline(std::cin, input);
		}
	}
	else
	{
		std::getline(std::cin, input);

	}

	Board b(getColor(input));
	// The opponent started the game so
	// the move has to be executed on the board.
	if (input.compare("Start") != 0)
	{
		b.executeMoveOnBoard(input);
		if (readFromFile)
		{
			b.stdPrintBoard();
		}
		
	}
	
	b.calculateAndExecuteMoveOnBoard();


	
	if (readFromFile)
	{
		b.stdPrintBoard();
	}
	while (true)
	{
		if (readFromFile)
		{
			if (std::getline(infile, line))
			{
				std::regex rgx("(\\w\\d+)-(\\w\\d+)");
				std::smatch match;
				std::regex_search(line, match, rgx);

				input = match[0];
			}
			else
			{
				std::getline(std::cin, input);
			}
		}
		else
		{
			std::getline(std::cin, input);
		}


		if (input.compare("Quit") == 0)
		{
			break;
		}
		else
		{
			b.executeMoveOnBoard(input);
			if (readFromFile)
			{
				b.stdPrintBoard();
				std::cout << "Move by opponent " << std::endl;
			}
			b.calculateAndExecuteMoveOnBoard();
			if (readFromFile)
			{
				b.stdPrintBoard();
				std::cout << "Move by AI " << std::endl;
			}
		}
	}
}