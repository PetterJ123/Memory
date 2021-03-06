#include "func.h"

int main()
{
	int row,
		col,
		p1Score = 0,
		p2Score = 0,
		scorePool = 0;
	std::string player1, player2, turn;
	std::map<int, int> gameboardMap; // Used to map card position to a gameboard index
	std::vector<int> indexV;
	indexV.push_back(-1);
	indexV.push_back(-1);
	char gameboard[20];
	bool cardPickedState = true;

	// Maps the board to index
	fillMap(gameboardMap);

	// Shuffle function, fills gameboard with random characters
	shuffleBoard(gameboard);

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
		renderGameboard(gameboard, indexV);

		// Asks for first card
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
		renderGameboard(gameboard, indexV);

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
		renderGameboard(gameboard, indexV);

		// If the characters are matching
		if (gameboard[indexV[0]] == gameboard[indexV[1]])
		{
			std::cout << "\nPOINT FOR " << turn << "\n";

			// Remove picked cards from gameboard
			gameboard[indexV[0]] = 32;
			gameboard[indexV[1]] = 32;

			checkPoints(p1Score,
						p2Score,
						player1,
						player2,
						scorePool,
						turn);

			// Prints current player points
			std::cout << player1 << ": " << p1Score << " pts\n"
					  << player2 << ": " << p2Score << " pts\n";

			pauseAndClear();
		}
		else
		{
			std::cout << "\nNO POINT FOR " << turn << "\n";

			std::cout << player1 << ": " << p1Score << " pts\n"
					  << player2 << ": " << p2Score << " pts\n";

			// Changes player turn
			if (turn == player1)
				turn = player2;
			else if (turn == player2)
				turn = player1;

			pauseAndClear();
		}

		indexV[0] = -1;
		indexV[1] = -1;
	}

	return 0;
}