#include "node.h"
node::node()
{
}


node::~node()
{
	
}

double node::getOutput()
{
	if (nodeType == 1)
	{
		//cout << "is an input node" << endl;
		return outputVal;
	}
	else
	{
		outputVal = 0;
		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			outputVal += inputs[i]->getOutput() * weights[i];
		}
		outputVal = activationFunction(outputVal + bias, 1);
		//cout << "subOut:" << outputVal << " ";
		return outputVal;
	}
}

double node::getLinOutput()
{
	if (nodeType == 1)
	{
		//cout << "is an input node" << endl;
		return outputVal;
	}
	else
	{
		outputVal = 0;
		outputLin = 0;
		for (unsigned int i = 0; i < inputs.size()/2; ++i)
		{
			outputVal += inputs[i]->getOutput() * weights[i];
		}
		outputVal = activationFunction(outputVal + bias, 1);

		for (unsigned int i = inputs.size() / 2; i < inputs.size(); ++i)
		{
			outputLin += inputs[i]->getOutput() * weights[i];
		}
		outputLin = linear(outputLin + biasLin, 1);
		//cout << "subOut:" << outputVal << " ";
		return outputVal;
	}
}


void node::addInputNode(node* newNode)
{
	inputs.push_back(newNode);
}


void node::assignRandomWeights()
{
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	normal_distribution<double> distribution(0, 1); //first parameter is the mean the second is the std deviation
	//cout << "weights:";
	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		weights.push_back(distribution(generator)); // assign weights
		//cout << weights[i] << ",";
	}
	bias = distribution(generator);
	biasLin = distribution(generator);
	//cout << endl;
}

void node::backPropogate(double target)
{
	if (nodeType == 2) // if it is an output node
	{
		nodeDelta = (outputVal - target)*activationFunctionDerivative(outputVal, 1);
		//cout << "nodeDelta:" << nodeDelta << endl;

		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			inputs[i]->backPropogate(nodeDelta*weights[i]);
		}
	}
	else if (nodeType == 0) // if it is a hidden node use target as the nodeDelta of the previous node multiplied by the weight it was passed down
	{
		nodeDelta += target*activationFunctionDerivative(outputVal, 1);
	}
}

void node::backLinPropogate(double target)
{
	if (nodeType == 2) // if it is an output node
	{
		nodeDelta = (outputVal - target)*activationFunctionDerivative(outputVal, 1); // error from normal feed forward
		//cout << "nodeDelta:" << nodeDelta << endl;

		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			inputs[i]->backPropogate(nodeDelta*weights[i]);
		}
		nodeDelta += (outputLin - target)*linearDerivative(outputLin, 1); // error from linear stuff dont back propogate
	}
	else if (nodeType == 0) // if it is a hidden node use target as the nodeDelta of the previous node multiplied by the weight it was passed down
	{
		nodeDelta += target*activationFunctionDerivative(outputVal, 1);
	}
}

void node::updateWeights(double learningRate)
{
	if (nodeDelta != 0)
	{
		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			weights[i] -= learningRate*nodeDelta*inputs[i]->getStoredOutput(); //update weight
		}
		bias -= learningRate*nodeDelta;//update bias
		biasLin -= learningRate*nodeDelta;
		nodeDelta = 0; // clear the node delta for next back propogation
		
		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			inputs[i]->updateWeights(learningRate);
		}
	}
	else
	{
		//cout << "done training\n";
	}
}

double node::unipolarSigmoid(double val, double lambda)
{
	return 1 / (1 + exp(-val*lambda));
}

double node::bipolarSigmoid(double val, double lambda)
{
	return (2 / (1 + exp(-val*lambda))) - 1;
}

double node::tanHyperbolic(double val, double lambda)
{
	return (exp(val*lambda) - exp(-val*lambda)) / (exp(val*lambda) + exp(-val*lambda));
}

double node::linear(double val, double lambda)
{
	return val*lambda;
}

double node::unipolarSigmoidDerivative(double val, double lambda)
{
	return lambda*val*(1 - val);
}

double node::bipolarSigmoidDerivative(double val, double lambda)
{
	return (lambda / 2)*(1 - pow(val, 2));
}

double node::tanHyperbolicDerivative(double val, double lambda)
{
	return lambda*(1-pow(val,2));
}

double node::linearDerivative(double val, double lambda)
{
	return lambda;
}

double node::activationFunction(double val, double lambda) //function allows for easy switching of activation functions
{
	//cout << "activation function val:" << val << " ";
	return bipolarSigmoid(val, lambda);
}

double node::activationFunctionDerivative(double val, double lambda) //quick function changing
{
	return bipolarSigmoidDerivative(val, lambda);
}