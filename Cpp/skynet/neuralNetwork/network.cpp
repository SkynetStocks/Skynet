#include "network.h"


network::network(unsigned int nuIn, unsigned int nuOut, unsigned int nuHidden, unsigned int nuWid, bool linearise)
	:inputs(nuIn), outputs(nuOut), hiddenLayers(nuHidden), width(nuWid)
{
	//cout << "inputs:" << inputs << " outputs:" << outputs << " hiddenLayers:" << hiddenLayers << " width:" << width << endl;
	linearNetworkLink = linearise;
	vector<node*> newLayer;
	for (unsigned int i = 0; i < outputs; ++i) //create output nodes
	{
		newLayer.push_back(new node);
		newLayer[i]->setNodeType(2);
	}
	nodeMesh.push_back(newLayer); //add to mesh


	for (unsigned int hL = 0; hL < hiddenLayers; ++hL) //creates hidden layers of a set width
	{
		newLayer.clear();
		for (unsigned int i = 0; i < width; ++i)
		{
			newLayer.push_back(new node);
		}
		nodeMesh.push_back(newLayer);
	}

	newLayer.clear();
	for (unsigned int i = 0; i < inputs; ++i) //create the input layer
	{
		newLayer.push_back(new node);
		newLayer[i]->setNodeType(1);
	}
	nodeMesh.push_back(newLayer);
	
	//now it is necessary to connect the nodes
	for (unsigned int i = 0; i < nodeMesh.size() - 1; ++i) //itterate through output and hidden layers skip input layer
	{
		for (unsigned int b = 0; b < nodeMesh[i].size(); ++b) //itterate through layer
		{
			for (unsigned int c = 0; c < nodeMesh[i + 1].size(); ++c) //itterate through layer after current layer
			{
				nodeMesh[i][b]->addInputNode(nodeMesh[i + 1][c]); //add an entry of the layer after current layer to the current layer
			}
			nodeMesh[i][b]->assignRandomWeights();
		}
	}
	//cout << "1\n";
	if (linearNetworkLink == true) //if linear component of network is wanted
	{
		//itterate through output and link to input layers
		for (unsigned int i = 0; i < nodeMesh[0].size(); ++i) //itterate through output nodes
		{
			//for each output node add input nodes
			for (unsigned int b = 0; b < nodeMesh[nodeMesh.size() - 1].size(); ++b) //itterate through input nodes
			{
				//cout << i << ", " << b << endl;
				//cout << nodeMesh[0][i] << endl;
				nodeMesh[0][i]->addInputNode(nodeMesh[nodeMesh.size()-1][b]); //link input node to output node
			}
			nodeMesh[0][i]->assignRandomWeights();
		}
	}
}


network::~network()
{
	for (unsigned int i = nodeMesh.size() - 1; i = 0; --i)	//deletes every node in the network
	{
		for (unsigned int b = nodeMesh[i].size() - 1; b = 0; --b)
		{
			delete nodeMesh[i][b];
		}
	}
}


void network::assignInputs(vector<double> in)
{
	unsigned int inputIndex = nodeMesh.size() - 1;
	for (unsigned int i = 0; i < in.size(); ++i)
	{
		//cout << "inputs:" << in[i] << endl;
		nodeMesh[inputIndex][i]->setOutput(in[i]);
	}
}

vector<double> network::getOutputs()
{
	//cout << "getting outputs\n";
	vector<double> out;
	if (linearNetworkLink == true)
	{
		for (unsigned int i = 0; i < outputs; ++i)
		{
			out.push_back(nodeMesh[0][i]->getOutput());
			//cout << "getOutputs" << out[i] << endl;
		}
	}
	else
	{
		for (unsigned int i = 0; i < outputs; ++i)
		{
			out.push_back(nodeMesh[0][i]->getOutput());
			//cout << "getOutputs" << out[i] << endl;
		}
	}
	return out;
}

double  network::train(vector<double> expectedOutputs, double learningRate)
{
	vector<double> outputs;
	for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
	{
		outputs.push_back(nodeMesh[0][i]->getStoredOutput());
	}

	double totalError = quadraticCost( outputs, expectedOutputs);
	if (linearNetworkLink == true)
	{
		for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
		{
			nodeMesh[0][i]->backPropogate(expectedOutputs[i]);
		}

		for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
		{
			nodeMesh[0][i]->updateWeights(learningRate);
		}
	}
	else
	{
		for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
		{
			nodeMesh[0][i]->backPropogate(expectedOutputs[i]);
		}

		for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
		{
			nodeMesh[0][i]->updateWeights(learningRate);
		}
	}
	return totalError;
}

double network::getError(vector<double> expectedOutputs)
{
	vector<double> outputs;
	for (unsigned int i = 0; i < nodeMesh[0].size(); ++i)
	{
		outputs.push_back(nodeMesh[0][i]->getStoredOutput());
	}

	double totalError = quadraticCost(outputs, expectedOutputs);

	return totalError;
}

void network::resetWeights()
{
	for (unsigned int i = 0; i < nodeMesh.size() - 1; ++i) //itterate through output and hidden layers skip input layer
	{
		for (unsigned int b = 0; b < nodeMesh[i].size(); ++b) //itterate through layer
		{
			nodeMesh[i][b]->assignRandomWeights(); //give the node a randomized weights
		}
	}
}

double network::quadraticCost(vector<double> output, vector<double> desiredOutput)
{
	double error = 0;
	for (unsigned int i = 0; i < output.size(); ++i)
	{
		error += pow(output[i] - desiredOutput[i], 2);
	}
	return error*0.5;
}
double network::quadraticCostDelta(double output, double desiredOutput)
{
	return output - desiredOutput;
}

