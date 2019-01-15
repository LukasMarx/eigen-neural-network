#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <ctime>
#include <random>


using namespace Eigen;

class Connect4{

	int** board;
	int height;
	int width;

public:
	Connect4(int Width, int Height);

	~Connect4();

	bool Play(int slot, int playerIndex);

	void UndoPlay(int slot);

	int RandomPlay();

	std::pair<int, int> MiniMaxPlay(int playerIndex, int slot, int depth);

	bool HasWon(int playerIndex);

	bool IsGameOver();

	void Print();

	MatrixXf Serialize();
};