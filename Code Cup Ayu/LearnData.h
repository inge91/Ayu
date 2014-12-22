#ifndef LEARNDATA_H
#define LEARNDATA_H


struct LearnData
{

	LearnData(int numberOfIslandsAI, int numberOfIslandsOpponent, 
			  int biggestIslandAI, int biggestIslandOpponent,
			  int smallestDistanceBetweenIslandAI, int smallestDistanceBetweenIslandOpponent)
	{
	}

	const int numberOfIslandsAI;
	const int numberOfIslandsOpponent;
	const int biggestIslandAI;
	const int biggestIslandOpponent;
	const int smallestDistanceBetweenIslandAI;
	const int smallestDistanceBetweenIslandOpponent;

	float randomMove;
};

#endif