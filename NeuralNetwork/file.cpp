#include "file.h"



std::pair < std::vector<MatrixXf>, std::vector<float> > File::ReadToMatrix(std::string fileName, int numInputs) {

	std::vector<MatrixXf> inputs;
	std::vector<float> targets;

	std::ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cout << "Error: Cannot read file: '" << fileName << "'!" << std::endl;
		exit(-1);
		return std::make_pair(std::vector<MatrixXf>(), std::vector<float>());
	}

	std::string line;

	int curLine = 0;
	while (std::getline(file, line))
	{
		std::istringstream lineStream(line);
		std::string element;
		bool isFirst = true;

		float* values = new float[numInputs]();
		int i = 0;
		while (std::getline(lineStream, element, ','))
		{

			if (isFirst)
			{
				int value = std::stoi(element, 0);
				targets.push_back(value);
				isFirst = false;
			}
			else
			{
				values[i - 1] = std::stof(element, 0);
			}
			i++;
		}

		MatrixXf m = Map<Matrix<float, Dynamic, Dynamic, RowMajor>>(values, numInputs,1);
		inputs.push_back(m);

		curLine++;
	}

	return std::make_pair(inputs, targets);
}