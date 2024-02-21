#include "T_Board.h"
#include <cctype>
using namespace std;

int main() {
	T_Board mainBoard;
	string inp = "";
	string buffer = "";
	string repeat = "";
	/*mainBoard.displayChoices();
	mainBoard.displayBoard();
	mainBoard.setBox("1", "X");
	mainBoard.displayBoard();
	mainBoard.setBox("5", "O");
	mainBoard.displayBoard();
	mainBoard.setBox("0", "X");
	mainBoard.displayBoard();
	mainBoard.setBox("6", "H");
	mainBoard.displayBoard();*/

	// Gameplay loop
		// Display choices
		// Turn
			// Player inputs box to play on
			// Check win condition
			// Repeat
		// Display winner
		// Repeat

	do {

		// Display choices to play on
		mainBoard.displayChoices();

		// Gameplay loop
		do {
			// Set inp to 'X' or 'O' depending on the turn
			if (mainBoard.getTurn() % 2 == 0)
				inp = "X";
			else
				inp = "O";

			// Player inputs box to play on
			cout << "Player " << (mainBoard.getTurn() % 2 + 1) << ", enter box (1-9): ";
			getline(cin, buffer);
			mainBoard.setBox(buffer, inp);
			mainBoard.displayBoard();

			// If the game is over, break out of gameplay loop
			if (mainBoard.gameOver())
				break;

			// If the game is not over, increment the turn number and repeat loop
			mainBoard.incTurn();
			continue;
		} while (!mainBoard.gameOver());

		// Display winner or a tie
		if (mainBoard.winner())
			cout << "Player " << (mainBoard.getTurn() % 2 + 1) << " wins!\n";
		else
			cout << "It's a tie!\n";

		// Clear board
		mainBoard.clearBoard();

		// Prompt for repeat
		do {
			cout << "Play again? (Y/N): ";
			getline(cin, repeat);

			if (repeat.length() != 1 && tolower(repeat[0]) != 'y' && tolower(repeat[0]) != 'n')
				cout << "Invalid: Press 'Y' to continue playing, or 'N' to exit.\n";
		} while (repeat.length() != 1 && tolower(repeat[0]) != 'y' && tolower(repeat[0]) != 'n');

	} while (tolower(repeat[0]) == 'y');
}