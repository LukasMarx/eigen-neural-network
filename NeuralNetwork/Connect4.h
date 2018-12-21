#pragma once
#include <iostream>

class Connect4{

	int** board;
	int height;
	int width;

public:
	Connect4(int Width, int Height);

	bool Play(int slot, int playerIndex);

	bool HasWon(int playerIndex);

	void Print();
};