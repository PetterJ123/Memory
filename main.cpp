#include "func.hpp"

int main()
{
	int row,
		col,
		p1Score = 0,
		&p1ScoreRef = p1Score,
		p2Score = 0,
		&p2ScoreRef = p2Score,
		scorePool = 0,
		&spRef = scorePool;
	std::string player1, player2, turn;
	std::map<int, int> gameboardMap; // Used to map card position to a gameboard index
	// In c++11 ability to initialize with list at declaration is possible
	std::vector<int> indexV;
	indexV.push_back(-1);
	indexV.push_back(-1);
	char gameboard[20],
		*gBoardPtr = gameboard;
	bool cardPickedState = true;

	// Maps the board to index
	fillMap(gameboardMap);

	// Shuffle function, fills gameboard with random characters
	shuffleBoard(gBoardPtr);

	// Asking for player names
	std::cout << "Name of player 1:";
	std::cin >> player1;

	std::cout << "Name of player 2:";
	std::cin >> player2;

	// Set turn to player1
	turn = player1;

	// Gameloop keeps game running
	while (true)
	{
		// Render gameboard
		renderGameboard(gBoardPtr, indexV);

		std::cout << "\n"
				  << turn
				  << ", first card flip: ";
		std::cin >> row >> col;

		// Flips card
		flipCard(row,
				 col,
				 gameboardMap,
				 indexV,
				 cardPickedState);

		// Render gameboard with asked position
		renderGameboard(gBoardPtr, indexV);

		std::cout << "\n"
				  << turn
				  << ", second card flip: ";
		std::cin >> row >> col;

		// Flips the second card
		flipCard(row,
				 col,
				 gameboardMap,
				 indexV,
				 cardPickedState);

		// Render gameboard with second asked position
		renderGameboard(gBoardPtr, indexV);

		// If the characters are matching
		if (gameboard[indexV[0]] == gameboard[indexV[1]])
		{
			std::cout << "\nPOINT FOR " << turn << "\n";

			// Remove picked cards from gameboard
			gameboard[indexV[0]] = 32;
			gameboard[indexV[1]] = 32;

			checkPoints(p1ScoreRef,
						p2ScoreRef,
						player1,
						player2,
						spRef,
						turn);

			pauseAndClear();
		}
		else
		{
			std::cout << "\nNO POINT FOR " << turn << "\n";
			pauseAndClear();
		}

		// Changes player turn
		if (turn == player1)
			turn = player2;
		else if (turn == player2)
			turn = player1;

		indexV[0] = -1;
		indexV[1] = -1;
	}

	return 0;
}