#pragma once
#include <string>
#include <iostream>
using namespace std;

class T_Board
{
private:
	string boxes[9];
	int turn;
	bool validateBox(string box) const;
	bool validateBoxInp(string inp) const;
public:
	T_Board();
	void clearBoard();
	void displayBoard() const;
	void displayChoices() const;
	void setBox(string box, string inp);
	int getTurn() const;
	void incTurn();
	bool winner() const;
	bool gameOver() const;
};

