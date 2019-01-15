#pragma once
#include <Eigen/Dense>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "json.hpp"
#include <fstream>

using namespace Eigen;
using json = nlohmann::json;

class NeuralNetwork {
public:
	int layercount;

	int* layers;

	float learningRate = 0.1;

	MatrixXf* weights;

	void train(MatrixXf* TrainingSets, MatrixXf* ExpectedResults, int NumTrainingSets, float LearningRate, int epochs);

	MatrixXf* feedForward(MatrixXf& Input);

	MatrixXf* query(MatrixXf& Input);

	void  propagateBack(MatrixXf* results, MatrixXf& expected, const float learningRate);

	NeuralNetwork(int* layers, int layercount);

	void save(std::string path);

	std::string serialize();
		
	void deserialize(std::string json);

	void load(std::string path);

	void reset();

};

