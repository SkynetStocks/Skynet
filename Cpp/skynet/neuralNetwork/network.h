#include "node.h"
#include <iostream>
using namespace std;
#pragma once
class network
{
public:
	network(unsigned int nuIn, unsigned int nuOut, unsigned int nuHidden, unsigned int nuWid, bool linearise);
	virtual ~network();
	void assignInputs(vector<double> iN); //should change input to vector
	vector<double> getOutputs();
	double train(vector<double> expectedOutputs, double learningRate); //queue rocky music
	double getError(vector<double> expectedOutputs); //returns the error of the last run
	void resetWeights();

	//get netork details
	unsigned int getNoInputs() { return inputs; }
	unsigned int getNoOutputs() { return outputs; }
	unsigned int getNoHiddenLayers() { return hiddenLayers; }
	unsigned int getHiddenLayerWidth() { return width; }
private:
	const unsigned int inputs, outputs, hiddenLayers, width; //holds the defined number of inputs and outputs of the network
	bool linearNetworkLink;
	vector<vector<node*>> nodeMesh;

	double quadraticCost(vector<double> output, vector<double> desiredOutput);
	double quadraticCostDelta(double output, double desiredOutput);
};

