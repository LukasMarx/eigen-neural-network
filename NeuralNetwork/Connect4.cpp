#include "Connect4.h";

Connect4::Connect4(int Width, int Height) {
	this->height = Height;
	this->width = Width;

	this->board = new int*[this->width];

	for (int i = 0; i < this->width; i++) {
		this->board[i] = new int[this->height]();
	}

}

bool Connect4::Play(int slot, int playerIndex) {
	int* column = this->board[slot];

	bool didPlace = false;
	for (int i = this->height - 1; i >= 0; i--) {
		if (column[i] == 0) {
			column[i] = playerIndex;
			didPlace = true;
			break;
		}
	}
	return HasWon(playerIndex);

}

bool Connect4::HasWon(int playerIndex) {
	// Horizontal
	for (int r = 0; r < this->height; r++) {
		int count = 0;
		for (int c = 0; c < this->width; c++) {
			if (this->board[c][r] == playerIndex) {
				count++;
			}
		}
		if (count >= 4) {
			return true;
		}
	}

	// Vertical
	for (int c = 0; c < this->width; c++) {
		int count = 0;
		for (int r = 0; r < this->height; r++) {
			if (this->board[c][r] == playerIndex) {
				count++;
			}
		}
		if (count >= 4) {
			return true;
		}
	}

	// Diagonal Left/Up to Right/Bottom
	for (int r = 0; r < this->height; r++) {

		int count = 0;
		for (int i = 0; i < this->width && i + r < this->height; i++) {
			if (this->board[i][r + i] == playerIndex) {
				count++;
			}
		}
		if (count >= 4) {
			return true;
		}
	}

	// Diagonal Left/Bottom to Right/Up
	for (int r = this->height - 1; r >= 0; r--) {

		int count = 0;
		for (int i = 0; i < this->width; i++) {
			if (this->board[i][r - i] == playerIndex) {
				count++;
			}
		}
		if (count >= 4) {
			return true;
		}
	}
	return false;
}

void Connect4::Print() {
	for (int r = 0; r < this->height; r++) {
		for (int c = 0; c < this->width; c++) {
			std::cout << this->board[c][r] <<" ";
		}
		std::cout << std::endl;
	}
}
