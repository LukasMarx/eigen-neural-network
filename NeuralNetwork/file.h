#pragma once
#include <Eigen/Dense>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<utility>

using namespace Eigen;

class File {
public:
	static std::pair < std::vector < MatrixXf> , std::vector<float> > ReadToMatrix(std::string path, int numInputs);
};