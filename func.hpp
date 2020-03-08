#ifndef FUNC_HPP
#define FUNC_HPP
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <time.h>

void pauseAndClear();
void pauseAndExit();
void checkPoints(int *p1Score,
				 int *p2Score,
				 std::string &p1,
				 std::string &p2,
				 int *sp,
				 std::string &turn);
void shuffleBoard(char *gBoardPtr);
void renderGameboard(char *gBoardPtr, std::vector<int> &indexV);
int intConcat(int n1, int n2);
void fillMap(std::map<int, int> &boardMap);

void pauseAndExit()
{
#if defined(__APPLE__)
	system("read -n 1 -s -p \"Press enter to exit...\"");
#elif defined(_WIN32)
	system("pause");
#elif defined(__gnu_linux__)
	system("read -n 1 -s -p \"Press enter to exit...\n");
#endif
	exit(EXIT_SUCCESS);
}

void checkPoints(int &p1Score,
				 int &p2Score,
				 std::string &p1,
				 std::string &p2,
				 int &pairs,
				 std::string &turn)
{
	if (turn == p1)
	{
		p1Score++;
		pairs++;
	}
	else if (turn == p2)
	{
		p2Score++;
		pairs++;
	}

	// If pairnumber is 10 evaluate how game ended
	if (pairs == 10)
	{
		if (p1Score > p2Score)
		{
			std::cout << p1 << " have won!\nScoreboard:\n"
					  << p1 << ": " << p1Score << "\n"
					  << p2 << ": " << p2Score << "\n";

			pauseAndExit();
		}
		else if (p1Score == p2Score)
		{
			std::cout << "This ended in a tie!\nScoreboard:\n"
					  << p1 << ": " << p1Score << "\n"
					  << p2 << ": " << p2Score << "\n";
			pauseAndExit();
		}
		else
		{
			std::cout << p2 << " have won!\nScoreboard:\n"
					  << p1 << ": " << p1Score << "\n"
					  << p2 << ": " << p2Score << "\n";
			pauseAndExit();
		}
	}
}

// Pauses execution and clears console window
// Macros for different pauses depending on platform
void pauseAndClear()
{
#if defined(__APPLE__)
	system("read -n 1 -s -p \"Press enter to continue...\"");
	system("clear");
#elif defined(_WIN32)
	system("pause");
	system("cls");
#elif defined(__gnu_linux__)
	system("read -n 1 -s -p \"Press enter to continue...\"");
	system("clear");
#endif
}

// Renderfunction
void renderGameboard(char *gBoardPtr, std::vector<int> &indexV)
{
	for (int i = 0; i < 20; i++)
	{
		if (i % 5 == 0)
		{
			if (i == 0)
				std::cout << "\n";
			else
				std::cout << "| \n";
		}

		if (i == indexV.at(0))
			std::cout << "| " << gBoardPtr[indexV.at(0)] << " ";
		else if (i == indexV.at(1))
			std::cout << "| " << gBoardPtr[indexV.at(1)] << " ";
		else if (gBoardPtr[i] == 32)
			std::cout << "| " << gBoardPtr[i] << " ";
		else
			std::cout << "| # ";
	}
	std::cout << "|";
}

// Shuffle function
void shuffleBoard(char *gBoardPtr)
{
	char gameBoard[20];
	char character = 'a';

	const int amnt = 20;   // Amount of numbers to generate
	const int maxNum = 20; // Highest allowed generated number
	int randomNumber;
	int randomNumberArr[amnt];
	srand((unsigned)time(0));	  // Seed for randomization
	for (int i = 0; i < amnt; i++) // Fill array with -1
		randomNumberArr[i] = -1;

	int index = 0;
	while (randomNumberArr[amnt - 1] == -1) // Loop until array empty of -1
	{
		randomNumber = (rand() % maxNum) + 1;
		bool exists = false;
		for (int i = 0; i < amnt; i++)
		{
			if (randomNumberArr[i] == randomNumber)
				exists = true;
		}

		if (!exists) // If random number already not in array, insert random number
		{
			randomNumberArr[index] = randomNumber;
			index++;
		}
	}

	// Place characters in gameboard
	for (int i = 0; i < 20; i++)
	{
		if (character > 106)
			character = 97; // Insert the doublettes in other half of the iteration

		int ranNum = randomNumberArr[i];
		gameBoard[ranNum] = character;
		character++;
	}

	// Create new gameboard to leftshft all elements
	for (int i = 0; i < 21; i++)
		gBoardPtr[i] = gameBoard[i + 1];
}

// Concatenates integers
int intConcat(int n1, int n2)
{
	std::string s1 = std::to_string(n1);
	std::string s2 = std::to_string(n2);

	std::string s3 = s1 + s2;

	int nr = std::stoi(s3);

	return nr;
}

// Fills the map with key values and their respective indexes
void fillMap(std::map<int, int> &boardMap)
{
	int k = 11;

	// Match up key to each index in gameboard
	for (int i = 0; i < 20; i++)
	{
		switch (k)
		{
		case 16:
			k = 21;
			break;
		case 26:
			k = 31;
			break;
		case 36:
			k = 41;
			break;
		}
		boardMap[k] = i;
		k++;
	}
}

// Function to turn a card around
void flipCard(int row,
			  int col,
			  std::map<int, int> &gbmap,
			  std::vector<int> &indexV,
			  bool &cardPickedState)
{
	int key = intConcat(row, col);
	int gameboardIndex = gbmap.at(key);

	// Card state altenator, alternates each time a card is picked
	if (cardPickedState)
	{
		indexV[0] = gameboardIndex;
		cardPickedState = false;
	}
	else
	{
		indexV[1] = gameboardIndex;
		cardPickedState = true;
	}
}

#endif