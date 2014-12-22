#include "MinimaxAlphaBetaPruning.h"


int alphabeta(Board b, int depth, bool isMaxValue)
{
	if (depth == 0)
	{
		return b.getIslandsOpponent().getNumberOfIslands() - b.getIslandsAI().getNumberOfIslands();
	}
	if (b.getGameWonBy() == b.getAIColor())
	{
		return 20;
	}
	else if (b.getGameWonBy() == b.getOpponentColor())
	{
		return -20;
	}
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> possibleActions = b.getIslandsAI().getPossibleActions();

	if (isMaxValue)
	{

		int maxScore = -9999;
		for (int i = 0; i < possibleActions.size(); i++)
		{
			Board* boardTemp = new Board(b);
			boardTemp->executeMoveOnBoard(possibleActions.at(i).first, possibleActions.at(i).second);

			int newScore = alphabeta(*boardTemp, depth - 1, false);
			if (newScore > maxScore)
			{
				maxScore = newScore;
			}
			delete boardTemp;
		}
		return maxScore;
	}
	else
	{
		int minScore = 9999;
		for (int i = 0; i < possibleActions.size(); i++)
		{

			Board* boardTemp = new Board(b);
			boardTemp->executeMoveOnBoard(possibleActions.at(i).first, possibleActions.at(i).second);
			int newScore = alphabeta(*boardTemp, depth - 1, true);
			if (newScore < minScore)
			{
				minScore = newScore;
			}
			delete boardTemp;
		}
		return minScore;
	}

}
