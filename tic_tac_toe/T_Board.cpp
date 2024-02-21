#include "T_Board.h"
using namespace std;

bool T_Board::validateBox(string box) const {
	// Return true if box is empty; return false if not

	// Check that box is within valid range (1-9)
	if (stoi(box) < 1 || stoi(box) > 9)
		return false;
	if (boxes[stoi(box) - 1] != " ")
		return false;
	else
		return true;
}
bool T_Board::validateBoxInp(string inp) const {
	// Return true if box inp is 'X' or 'O' (or lowercase version); return false if not
	if (tolower(inp[0]) == 'x' || tolower(inp[0]) == 'o')
		return true;
	else
		return false;
}
T_Board::T_Board() {
	// Call clearBoard()
	clearBoard();
}
void T_Board::clearBoard() {
	// Initialize each box in boxes to a single space & reset turn to 1
	for (int i = 0; i < 9; i++)
		boxes[i] = " ";
	turn = 0;
}
void T_Board::displayBoard() const {
	// Display the board & Xs and Os if there are any
	cout << " " << boxes[0] << " | " << boxes[1] << " | " << boxes[2] << " \n";
	cout << "-----------\n";
	cout << " " << boxes[3] << " | " << boxes[4] << " | " << boxes[5] << " \n";
	cout << "-----------\n";
	cout << " " << boxes[6] << " | " << boxes[7] << " | " << boxes[8] << " \n";
}
void T_Board::displayChoices() const {
	// Display a labelled board for users' reference
	cout << " 1 | 2 | 3 \n";
	cout << "-----------\n";
	cout << " 4 | 5 | 6 \n";
	cout << "-----------\n";
	cout << " 7 | 8 | 9 \n";
}
void T_Board::setBox(string box, string inp) {
	// After ensuring the box param is currently empty, and that inp is valid, store inp into boxes[box]

	// Validate box is empty
	while (!validateBox(box)) {
		cout << "Invalid box. Try again: \n";
		getline(cin, box);
	}

	// Validate inp is 'X' or 'O' (or lowercase)
	while (!validateBoxInp(inp)) {
		cout << "Invalid input. Try again: \n";
		getline(cin, inp);
	}

	// Now that data is valid, store in the corresponding box.
	boxes[stoi(box) - 1] = inp;

	return;
}
int T_Board::getTurn() const {
	// Get the value stored in turn
	return turn;
}
void T_Board::incTurn() {
	// Increase the value stored in turn by 1
	turn++;
}
bool T_Board::winner() const {
	// Check if there is a winner!

	// Check for three in a row
	for (int i = 0; i < 9; i += 3)
		if (boxes[i] != " " && boxes[i] == boxes[i + 1] && boxes[i + 1] == boxes[i + 2] && boxes[i + 2] == boxes[i])
			return true;

	// Check for three in a column
	for (int i = 0; i < 3; i++)
		if (boxes[i] != " " && boxes[i] == boxes[i + 3] && boxes[i + 3] == boxes[i + 6] && boxes[i + 6] == boxes[i])
			return true;

	// Check for diagonal (top right to bottom left)
	if (boxes[2] != " " && boxes[2] == boxes[4] && boxes[4] == boxes[6] && boxes[6] == boxes[2])
		return true;

	// Check for diagonal (top left to bottom right)
	if (boxes[0] != " " && boxes[0] == boxes[4] && boxes[4] == boxes[8] && boxes[8] == boxes[0])
		return true;

	// If conditions for a winner have not been met, return false
	return false;
}
bool T_Board::gameOver() const {
	// Check if board is full or if win condition has been met. If so, return true; else, return false

	// This is a flag that will be set to false if any boxes do not have an X or O
	bool fullBoard = true;

	// Check each box; if any box does not have an X or an O, set fullBoard to false
	for (string str : boxes) {
		if (str != "X" && str != "O") {
			fullBoard = false;
			break;
		}
	}

	// If the board is full or if there is a winner, return true
	if (fullBoard || winner())
		return true;

	// Otherwise, return false
	return false;
}