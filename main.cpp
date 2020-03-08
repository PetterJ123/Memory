#include "func.hpp"

int main()
{
	int playerScore1,
		playerScore2,
		row,
		col,
		counter = 0,
		*counterPtr = &counter;
	std::string player1, player2, turn;
	std::map<int, int> gameboardMap; // Used to map card position to a gameboard index
	std::vector<int> indexV;
	indexV.push_back(-1);
	indexV.push_back(-1);
	char gameboard[20],
		*gBoardPtr = gameboard;
	bool h = true, gameloop = true;

	// maps the board to index
	fillMap(gameboardMap);

	// shuffle function, fills gameboard with random characters
	shuffleBoard(gBoardPtr);

	// asking for player names
	std::cout << "Name of player 1:";
	std::cin >> player1;

	std::cout << "Name of player 2:";
	std::cin >> player2;

	// set turn to player1
	turn = player1;

	// cheat
	std::map<int, int>::iterator it = gameboardMap.begin();
	int i = 0;
	while (it != gameboardMap.end())
	{
		std::cout << it->first << " : " << it->second << " : " << gameboard[i] << "\n";
		i++;
		it++;
	}

	// gameloop keep game running
	while (gameloop)
	{
		// render gameboard
		renderGameboard(gBoardPtr, indexV);

		std::cout << "\n"
				  << turn
				  << ", first card flip: ";
		std::cin >> row >> col;

		// flips card
		flipCard(row,
				 col,
				 gameboardMap,
				 indexV,
				 h);

		// render gameboard with asked position
		renderGameboard(gBoardPtr, indexV);

		std::cout << "\n"
				  << turn
				  << ", second card flip: ";
		std::cin >> row >> col;

		// flips the second card
		flipCard(row,
				 col,
				 gameboardMap,
				 indexV,
				 h);

		// render gameboard with second asked position
		renderGameboard(gBoardPtr, indexV);

		// if the characters are alike
		if (gameboard[indexV[0]] == gameboard[indexV[1]])
		{
			std::cout << "\nPOINT FOR " << turn << "\n";
			gameboard[indexV[0]] = 32;
			gameboard[indexV[1]] = 32;
			pauseAndClear();
		}
		else
		{
			std::cout << "\nno point\n";
			pauseAndClear();
		}

		// changes turn
		if (turn == player1)
			turn = player2;
		else if (turn == player2)
			turn = player1;

		indexV[0] = -1;
		indexV[1] = -1;
	}

	return 0;
}