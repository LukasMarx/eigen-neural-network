#pragma once
#include <Eigen/Dense>
#include <stdlib.h>
#include <iostream>
#include <random>

using namespace Eigen;

	class NeuralNetwork {
	public:
		int layercount;

		int* layers;

		float learningRate = 0.1;

		MatrixXf* weights;

		void train(MatrixXf* TrainingSets, MatrixXf* ExpectedResults, int NumTrainingSets);

		MatrixXf* feedForward(MatrixXf& Input);

		MatrixXf* query(MatrixXf& Input);

		void  propagateBack(MatrixXf* results, MatrixXf& expected, const float learningRate);

		NeuralNetwork(int* layers, int layercount);

	};

