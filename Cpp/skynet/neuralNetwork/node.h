#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
using namespace std;
#pragma once

class node
{
public:
	node();
	virtual ~node();
	double getOutput();
	double getLinOutput();
	double getStoredOutput() { return outputVal; }
	void addInputNode(node*);
	void setOutput(double val) { outputVal = val; }
	void setNodeType(short iN) { nodeType = iN; } //0 = hiddnet layer, 1 = input, 2 = output
	void assignRandomWeights();

	void backPropogate(double target);
	void backLinPropogate(double target);
	void updateWeights(double learningRate);

	double activationFunction(double val, double lambda);
	double node::activationFunctionDerivative(double val, double lambda);

	double linear(double val, double lambda);
	double linearDerivative(double val, double lambda);
private:
	double outputVal;
	double outputLin;
	short nodeType = 0; //defaults to either output or hidden layer node

	vector<node*> inputs;

	vector<double> weights;
	double bias;
	double biasLin;
	double nodeDelta = 0;

	//activation functions and their derivatives
	double unipolarSigmoid(double val, double lambda);
	double bipolarSigmoid(double val, double lambda);
	double tanHyperbolic(double val, double lambda);

	double unipolarSigmoidDerivative(double val, double lambda);
	double bipolarSigmoidDerivative(double val, double lambda);
	double tanHyperbolicDerivative(double val, double lambda);
};

