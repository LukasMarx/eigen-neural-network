#include "NeuralNetwork.h"

float gaussRandom(float center, float scale, std::default_random_engine r)
{
	std::normal_distribution<float> distribution(center, scale);

	float temp = distribution(r);

	return temp;
}


NeuralNetwork::NeuralNetwork(int* layers, int layercount) {
	this->layercount = layercount;
	this->layers = layers;
	this->weights = new MatrixXf[layercount]();

	std::random_device rd;

	for (int i = 1; i < layercount; i++) {


		weights[i - 1] = MatrixXf(layers[i], layers[i - 1]);

		int width = weights[i - 1].cols();
		int height = weights[i - 1].rows();

		for (int j = 0; j < width; j++) {
			for (int k = 0; k < height; k++) {
				std::random_device rd;

				std::mt19937 e2(rd());

				weights[i - 1](k, j) = gaussRandom(0.0, pow(width, -0.5), e2);
			}
		}
	}
}


void NeuralNetwork::train(MatrixXf* TrainingSets, MatrixXf* ExpectedResults, int NumTrainingSets)
{
	int epochsLearning = 5;


	for (int i = 0; i < epochsLearning; i++)
	{
		for (int j = 0; j < NumTrainingSets; j++)
		{
			MatrixXf* results = this->feedForward(TrainingSets[j]);

			this->propagateBack(results, ExpectedResults[j], 0.06F);

			delete[] results;
		}
	}
}



MatrixXf* NeuralNetwork::feedForward(MatrixXf& Input) 
{

	MatrixXf* results = new MatrixXf[this->layercount]();
	results[0] = Input;

	for (int i = 1; i < this->layercount; i++) {

		results[i] = this->weights[i - 1]* results[i - 1];

		results[i] = results[i].unaryExpr([](float x) {return 1.0 / (1.0 + exp(-1 * x)); });
	}
	return results;
}

MatrixXf* NeuralNetwork::query(MatrixXf& Input) 
{

	return this->feedForward(Input);
}


void  NeuralNetwork::propagateBack(MatrixXf* results, MatrixXf& expected, const float learningRate)
{
	MatrixXf prevError;


	for (int i = this->layercount - 1; i >= 1; i--) {

		MatrixXf inputs = results[i - 1];
		MatrixXf outputs = results[i];

		MatrixXf error;

		if (i == layercount - 1) {

			error = expected - outputs;

		}
		else {

			error = this->weights[i].transpose() *  prevError;
		}

		MatrixXf one(outputs.rows(), outputs.cols());
		one.setConstant(1.0F);
		
		error = outputs.cwiseProduct(error).cwiseProduct(one - outputs);

		MatrixXf delta =  (error * inputs.transpose()) * 0.3F;


		this->weights[i - 1] = delta  + this->weights[i - 1];


		prevError = error;

	}

}


