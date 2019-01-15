
#include <iostream>
#include "file.h"
#include "NeuralNetwork.h"
#include "TimeLogger.h"
#include <string>
#include "Connect4.h"

using namespace Eigen;

//float normalize(float x) {
//
//	return (x / 2 * 0.99) + 0.01;
//}
//
//void normalizeVector(std::vector<MatrixXf>& input) {
//
//	for (int i = 0; i < input.size(); i++) {
//		input.at(i) = input.at(i).unaryExpr(&normalize);
//	}
//}
//
//std::vector<MatrixXf> convertTargets(std::vector<float>& rawTargets, int outputHeight) {
//	std::vector<MatrixXf> targets;
//	for (int i = 0; i < rawTargets.size(); i++)
//	{
//		MatrixXf m = MatrixXf(outputHeight,1 );
//		
//		m.setConstant(0.01);
//
//		m(rawTargets.at(i), 0) = 0.99;
//
//		targets.push_back(m);
//	}
//	return targets;
//}
//
//int main(int argc, char* argv[])
//{
//
//
//	int layers[4] = { 42, 42, 7 };
//	NeuralNetwork* nn = new NeuralNetwork(layers, 3);
//
//
//	std::pair<std::vector<MatrixXf>, std::vector<float> > trainingData = File::ReadToMatrix("train.csv", 42);
//	std::vector<MatrixXf> trainingsSets = trainingData.first;
//	std::vector<float> expectedResults = trainingData.second;
//
//	normalizeVector(trainingData.first);
//	std::vector<MatrixXf> rightTargets = convertTargets(trainingData.second, 7);
//
//
//	TimeLogger* time = new TimeLogger("Training");
//	time->start();
//	nn->train(&trainingData.first[0], &rightTargets[0], trainingData.first.size(), 0.03F, 1);
//	time->stopWatchAndLog();
//
//	nn->save("out.json");
//
//	nn = new NeuralNetwork(layers, 3);
//
//	nn->load("out.json");
//
//
//	// --------------- TEST ------------------
//
//
//	std::pair<std::vector<MatrixXf>, std::vector<float> > testData = File::ReadToMatrix(std::string("train.csv"), 42);
//	normalizeVector(testData.first);
//
//
//
//	int numberCorrectGuesses = 0;
//	int resultCount[7] = { 0,0,0,0,0,0,0 };
//	for (int i = 0; i < testData.first.size(); i++) {
//
//		MatrixXf* results = nn->query(testData.first.at(i));
//
//		MatrixXf result = results[2];
//
//		int highest = 0;
//
//		for (int j = 0; j < 7; j++)
//		{
//			if ((result)(j,0) > (result)(highest,0))
//			{
//				highest = j;
//			}
//		}
//		resultCount[highest]++;
//		if (highest == testData.second.at(i))
//		{
//
//			numberCorrectGuesses++;
//
//		}
//		
//
//		delete[] results;
//	}
//
//	for (int i = 0; i < 7; i++) {
//		std::cout << resultCount[i] << ", ";
//	}
//
//
//	float result = (numberCorrectGuesses / ((float)testData.first.size())) * 100;
//	std::cout.precision(5);
//
//	std::cout << result << "%" << std::endl;
//}
//

MatrixXf CreateOutput(int slot, int numSlots) {
	MatrixXf m = MatrixXf(numSlots, 1);

	m.setConstant(0.01);

	m(slot, 0) = 0.99;

	return m;
}

int VectorToNumber(MatrixXf& input) {

	int highest = 0;

	for (int j = 0; j < 7; j++)
	{
		if ((input)(j, 0) > (input)(highest, 0))
		{
			highest = j;
		}
	}
	return highest;
}


void PlayOneGame(NeuralNetwork& A, NeuralNetwork& B, std::vector<MatrixXf>& trainDataA, std::vector<MatrixXf>& resultsA, std::vector<MatrixXf>& trainDataB, std::vector<MatrixXf>& resultsB) {
	
	int numSlots = 7;
	Connect4* connect = new Connect4(numSlots, 6);

	int player = 1;
	int playCount = 0;
	int randomPlayCount = 0;
	while (true) {

		std::vector<MatrixXf> boardsA;
		std::vector<MatrixXf> boardsB;
		std::vector<MatrixXf> playsA;
		std::vector<MatrixXf> playsB;

		MatrixXf boardBeforePlay = connect->Serialize();
		
		//connect->Print();

		int slot;
		
		if (player == 1) {
			slot = VectorToNumber(*A.query(boardBeforePlay));
		}
		else {
			slot = VectorToNumber(*B.query(boardBeforePlay));
		}

		bool didPlace = connect->Play(slot, player);

		if (!didPlace) {
			slot = connect->RandomPlay();
			connect->Play(slot, player);
			randomPlayCount++;
		}

		bool won = connect->HasWon(player);

		if (player == 1) {
			playsA.push_back(CreateOutput(slot, numSlots));
			boardsA.push_back(boardBeforePlay);
		}
		else {
			playsB.push_back(CreateOutput(slot, numSlots));
			boardsB.push_back(boardBeforePlay);
		}

		if (won) {
			if (player == 1) {
				trainDataA.insert(trainDataA.end(), boardsA.begin(), boardsA.end());
				resultsA.insert(resultsA.end(), playsA.begin(), playsA.end());

				playsB.clear();
				boardsB.clear();
				
			}
			else {
				trainDataB.insert(trainDataB.end(), boardsB.begin(), boardsB.end());
				resultsB.insert(resultsB.end(), playsB.begin(), playsB.end());
				playsA.clear();
				boardsA.clear();
				
			}
			std::cout << playCount << ", " << randomPlayCount << ", " << player << std::endl;
			return;
		}

		if (connect->IsGameOver()) {
			return;
		}

		if (player == 1) {
			
			player = 2;
		}
		else {
			player = 1;
		}
		playCount++;

	}

	delete connect;
}

void main() {
	/*std::vector<MatrixXf> trainDataA;
	std::vector<MatrixXf> trainDataB;
	std::vector<MatrixXf> resultsA;
	std::vector<MatrixXf> resultsB;

	int layers[4] = { 42, 42, 7 };

	NeuralNetwork* A = new NeuralNetwork(layers, 3);
	NeuralNetwork* B = new NeuralNetwork(layers, 3);

	
	for (int j = 0; j < 1000; j++) {
		for (int i = 0; i < 100; i++) {
			PlayOneGame(*A, *B, trainDataA, resultsA, trainDataB, resultsB);
		}
		if (trainDataA.size() > 0) {
			A->reset();
			A->train(&trainDataA[0], &resultsA[0], trainDataA.size(), 0.5F, 10);
		}
		
		if (trainDataB.size() > 0) {
			B->reset();
			B->train(&trainDataB[0], &resultsB[0], trainDataB.size(), 0.5F, 10);
		}
	}*/

	int numSlots = 7;
	Connect4* connect = new Connect4(numSlots, 6);

	int currentPlayer = 1;

	while (true) {
		if (connect->IsGameOver()) {
			return;
		}

		if (currentPlayer == 1) {
			std::string slot;

			std::cin >> slot;

			connect->Play(std::stoi(slot), currentPlayer);

			if (connect->HasWon(currentPlayer)) {
				std::cout << "Player 1 has won!";
			}

			currentPlayer = 2;
		}
		else {
			auto move = connect->MiniMaxPlay(currentPlayer, 0, 0);

			connect->Play(move.first, currentPlayer);

			if (connect->HasWon(currentPlayer)) {
				std::cout << "Player 2 has won!";
			}
			currentPlayer = 1;
		}

		connect->Print();

	}

}