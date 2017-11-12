#include "node.h"
#include <iostream>
using namespace std;
#pragma once
class network
{
public:
	network(unsigned int nuIn, unsigned int nuOut, unsigned int nuHidden, unsigned int nuWid);
	virtual ~network();
	void assignInputs(vector<double> iN); //should change input to vector
	vector<double> getOutputs();
	double train(vector<double> expectedOutputs, double learningRate); //queue rocky music
private:
	const unsigned int inputs, outputs, hiddenLayers, width; //holds the defined number of inputs and outputs of the network
	vector<vector<node*>> nodeMesh;

	double quadraticCost(vector<double> output, vector<double> desiredOutput);
	double quadraticCostDelta(double output, double desiredOutput);
};

