#include "Connect4.h";


Connect4::Connect4(int Width, int Height) {
	this->height = Height;
	this->width = Width;

	this->board = new int*[this->width];

	for (int i = 0; i < this->width; i++) {
		this->board[i] = new int[this->height]();
	}

}

Connect4::~Connect4() {
	for (int i = 0; i < this->width; i++) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

int Connect4::RandomPlay() {
	std::random_device rd;

	std::mt19937 e2(rd());

	std::uniform_int_distribution<> distr(0, 6);

	for (int i = 0; i < 100; i++) {
		int random = (int)distr(e2);
		if (this->board[random][0] == 0) {
			return random;
		}
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
	return didPlace;
}

void Connect4::UndoPlay(int slot) {
	int* column = this->board[slot];

	for (int i = 0; i < this->height; i++) {
		if (column[i] != 0) {
			column[i] = 0;
			break;
		}
	}
}

bool Connect4::IsGameOver() {
	for (int c = 0; c < this->width; c++) {
		if (this->board[c][0] == 0) {
			return false;
		}
	}
	return true;
}

bool Connect4::HasWon(int playerIndex) {
	// Horizontal
	for (int r = 0; r < this->height; r++) {
		int count = 0;
		for (int c = 0; c < this->width; c++) {
			if (this->board[c][r] == playerIndex) {
				count++;
			}
			else {
				count = 0;
			}
			if (count >= 4) {
				return true;
			}
		}
		
	}

	// Vertical
	for (int c = 0; c < this->width; c++) {
		int count = 0;
		for (int r = 0; r < this->height; r++) {
			if (this->board[c][r] == playerIndex) {
				count++;
			}
			else {
				count = 0;
			}
			if (count >= 4) {
				return true;
			}
		}
		
	}

	// Diagonal Left/Up to Right/Bottom
	for (int r = 0; r < this->height; r++) {

		int count = 0;
		for (int i = 0; i < this->width && i + r < this->height; i++) {
			if (this->board[i][r + i] == playerIndex) {
				count++;
			}
			else {
				count = 0;
			}
			if (count >= 4) {
				return true;
			}
		}
		
	}

	// Diagonal Left/Bottom to Right/Up
	for (int r = this->height - 1; r >= 0; r--) {

		int count = 0;
		for (int i = 0; i < this->width; i++) {
			if (this->board[i][r - i] == playerIndex) {
				count++;
			}
			else {
				count = 0;
			}
			if (count >= 4) {
				return true;
			}
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
	std::cout << std::endl;
}

MatrixXf Connect4::Serialize() {

	MatrixXf result(this->height * this->width, 1);

	for (int r = 0; r < this->height; r++) {
		int count = 0;
		for (int c = 0; c < this->width; c++) {
			result(count,0) = (this->board[r][c] /2 * 0.99) + 0.01;
			count++;
		}
	}
	return result;
}

std::pair<int, int> Connect4::MiniMaxPlay(int playerIndex, int slot, int depth) {
	if (playerIndex == 2 && this->HasWon(2)) {
		return std::make_pair(slot, 10);
	}
	else if(playerIndex == 2 && this->HasWon(1)) {
		return std::make_pair(slot, -10);
	}
	else if(this->IsGameOver() || depth > 8) {
		return std::make_pair(slot, 0);
	}

	// <slot, score>
	int score = -2;
	int winningSlot = 0 ;

	for (int c = 0; c < this->width; c++) {
		if (this->Play(c, 2)) {
			
			if (playerIndex == 1) {
				auto move = MiniMaxPlay(2, c, depth +1);
				if (playerIndex == 2 && move.second > score) {
					score = move.second;
					winningSlot = c;
				}
				if (playerIndex == 1 && move.second < score) {
					score = move.second;
					winningSlot = c;
				}

			}
			else {
				auto move = MiniMaxPlay(1, c, depth + 1);
				if (playerIndex == 2 && move.second > score) {
					score = move.second;
					winningSlot = c;
				}
				if (playerIndex == 1 && move.second < score) {
					score = move.second;
					winningSlot = c;
				}
			}
			this->UndoPlay(c);
		}
	}
	
	return std::make_pair(winningSlot, score);



}
