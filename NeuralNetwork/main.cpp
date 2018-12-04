#include <iostream>
#include "pch.h"
#include "file.h"
#include "NeuralNetwork.h"
#include "TimeLogger.h"
#include <string>

using namespace Eigen;

float normalize(float x) {

	return (x / 255 * 0.99) + 0.01;
}

void normalizeVector(std::vector<MatrixXf>& input) {

	for (int i = 0; i < input.size(); i++) {
		input.at(i) = input.at(i).unaryExpr(&normalize);
	}
}

std::vector<MatrixXf> convertTargets(std::vector<float>& rawTargets, int outputHeight) {
	std::vector<MatrixXf> targets;
	for (int i = 0; i < rawTargets.size(); i++)
	{
		MatrixXf m = MatrixXf(outputHeight,1 );
		
		m.setConstant(0.01);

		m(rawTargets.at(i), 0) = 0.99;

		targets.push_back(m);
	}
	return targets;
}

int main(int argc, char* argv[])
{


	int layers[3] = { 784, 200 ,10 };
	NeuralNetwork* nn = new NeuralNetwork(layers, 3);


	std::pair<std::vector<MatrixXf>, std::vector<float>> trainingData = File::ReadToMatrix("mnist_train.csv", 784);
	std::vector<MatrixXf> trainingsSets = trainingData.first;
	std::vector<float> expectedResults = trainingData.second;

	normalizeVector(trainingData.first);
	std::vector<MatrixXf> rightTargets = convertTargets(trainingData.second, 10);


	TimeLogger* time = new TimeLogger("Training");
	time->start();
	nn->train(&trainingData.first[0], &rightTargets[0], trainingData.first.size());
	time->stopWatchAndLog();

	// --------------- TEST ------------------


	std::pair<std::vector<MatrixXf>, std::vector<float>> testData = File::ReadToMatrix(std::string("mnist_test.csv"), 784);
	normalizeVector(testData.first);



	int numberCorrectGuesses = 0;
	for (int i = 0; i < testData.first.size(); i++) {

		MatrixXf* results = nn->query(testData.first.at(i));

		MatrixXf result = results[2];

		int highest = 0;
		for (int j = 0; j < 10; j++)
		{
			if ((result)(j,0) > (result)(highest,0))
			{
				highest = j;
			}
		}
		if (highest == testData.second.at(i))
		{

			numberCorrectGuesses++;

		}
		
		delete[] results;
	}

	float result = (numberCorrectGuesses / ((float)testData.first.size())) * 100;
	std::cout.precision(5);

	std::cout << result << "%" << std::endl;
}

