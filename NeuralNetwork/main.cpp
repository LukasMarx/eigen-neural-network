
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

void main() {
	Connect4* connect = new Connect4(7, 6);

	int player = 1;
	while (true) {
		std::string slot;
		std::getline(std::cin, slot);

		bool won = connect->Play(std::stoi(slot), player);
		connect->Print();

		if (won) {
			std::cout << "player " << player << " won!";
			return;
		}

		if (player == 1) {
			player = 2;
		}
		else {
			player = 1;
		}


	}
	

	
}