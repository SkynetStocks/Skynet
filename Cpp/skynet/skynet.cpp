#include "skynet.h"



skynet::skynet()
{
}


skynet::~skynet()
{
	if (net != nullptr)
		delete net;
	if (sS != nullptr)
		delete sS;
}

bool skynet::intitalise(const char* stock, date_time minDate, date_time maxDate, unsigned int inputs, unsigned int outputs, unsigned int hiddenLayers, unsigned int width)
{
	stockLoader sL; // creates stock loading object
	if (sL.initialise() != true)
		return false;
	sS = sL.loadStock(stock, minDate, maxDate); //loads values from stock KO stores values in a stockSampler Object

	net = new network(inputs, outputs, hiddenLayers, width); //create network

	//setup normalization values
	double max = sS->getMaxValue();
	cout << "maxVal:" << max << endl;
	normalizationScalar = 2 / (max*1.2); //1.2*max gives room for value to increase past the max by 20% places in range of [0,2]
	cout << "normalizationScalar:" << normalizationScalar << endl;
	offset = -1; // to place in range of [-1,1]
	return true;
}
void skynet::train(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, double learningRate)
{
	vector<double> inputs, output, networkOutput, outputAnalysis, networkOutputAnalysis, diffSquared;
	double uncertaintyOfOutput, error;

	date_time subStart = start, subEnd = start; //start and end dates for the subset
	subEnd.addSeconds(subSampleLength);
	date_time outputPoint = subEnd; // output point time
	outputPoint.addSeconds(outputDistance);
	int stepsize = start.diffSeconds(end) / noItt;
	cout << "stepsize:" << stepsize << endl;

	for (unsigned int i = 0; i < noItt; ++i)
	{
		cout << "subStart:" << subStart.getYearI() << "," << subStart.getMonthUI() << "," << subStart.getDayUI() << "," << subStart.getHourI() << "," << subStart.getMinuteI() << "," << subStart.getSecondI() << endl;
		//cout << "subEnd:" << subEnd.getYearI() << "," << subEnd.getMonthUI() << "," << subEnd.getDayUI() << "," << subEnd.getHourI() << "," << subEnd.getMinuteI() << "," << subEnd.getSecondI() << endl;
		stockSampler* subSet = sS->getSubset(subStart, subEnd, net->getNoInputs() - 1, 1);
		inputs = subSet->getPointsd();

		//cout << "inputs:";
		for (unsigned int b = 0; b < inputs.size(); ++b) // normalize inputs
		{
			inputs[b] = normalize(inputs[b]);
			//cout << inputs[b] << ",";
		}
		cout << endl;

		output.push_back(normalize(sS->getValue(outputPoint, uncertaintyOfOutput)));

		net->assignInputs(inputs);
		networkOutput = net->getOutputs();
		networkOutputAnalysis.push_back(denormalize(networkOutput[0]));
		outputAnalysis.push_back(denormalize(output[0]));
		error = net->getError(output);
		diffSquared.push_back(pow(denormalize(networkOutput[0])- denormalize(output[0]),2));
		cout << "learningRate:" << learningRateFunction(error,learningRate) << endl;
		net->train(output, learningRateFunction(error, learningRate));
		//cout << "networkOutput:" << denormalize(networkOutput[0]) << " targetOutput" << denormalize(output[0]) << endl;
		//cout << "error:" << error << endl << endl;


		delete subSet;
		output.clear();
		subStart.addSeconds(stepsize);
		subEnd.addSeconds(stepsize);
		outputPoint.addSeconds(stepsize);
	}

	vector<vector<double>> analysisData;
	analysisData.push_back(networkOutputAnalysis);
	analysisData.push_back(outputAnalysis);
	analysisData.push_back(diffSquared);
	createCSV(analysisData, "trainingData.csv");


}
void skynet::run(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance)
{
	vector<double> inputs, output, networkOutput, outputAnalysis, networkOutputAnalysis;
	double uncertaintyOfOutput;

	date_time subStart = start, subEnd = start; //start and end dates for the subset
	subEnd.addSeconds(subSampleLength);
	date_time outputPoint = subEnd; // output point time
	outputPoint.addSeconds(outputDistance);
	int stepsize = start.diffSeconds(end) / noItt;
	//cout << "stepsize:" << stepsize << endl;

	for (unsigned int i = 0; i < noItt; ++i)
	{
		cout << "subStart:" << subStart.getYearI() << "," << subStart.getMonthUI() << "," << subStart.getDayUI() << "," << subStart.getHourI() << "," << subStart.getMinuteI() << "," << subStart.getSecondI() << endl;
		//cout << "subEnd:" << subEnd.getYearI() << "," << subEnd.getMonthUI() << "," << subEnd.getDayUI() << "," << subEnd.getHourI() << "," << subEnd.getMinuteI() << "," << subEnd.getSecondI() << endl;
		stockSampler* subSet = sS->getSubset(subStart, subEnd, net->getNoInputs() - 1, 1);
		inputs = subSet->getPointsd();

		//cout << "inputs:";
		for (unsigned int b = 0; b < inputs.size(); ++b) // normalize inputs
		{
			inputs[b] = normalize(inputs[b]);
			//cout << inputs[b] << ",";
		}
		cout << endl;

		output.push_back(normalize(sS->getValue(outputPoint, uncertaintyOfOutput)));

		net->assignInputs(inputs);
		networkOutput = net->getOutputs();
		networkOutputAnalysis.push_back(denormalize(networkOutput[0]));
		outputAnalysis.push_back(denormalize(output[0]));

		//cout << "networkOutput:" << denormalize(networkOutput[0]) << " targetOutput" << denormalize(output[0]) << endl;


		delete subSet;
		output.clear();
		subStart.addSeconds(stepsize);
		subEnd.addSeconds(stepsize);
		outputPoint.addSeconds(stepsize);
	}

	vector<vector<double>> analysisData;
	analysisData.push_back(networkOutputAnalysis);
	analysisData.push_back(outputAnalysis);
	createCSV(analysisData, "runData.csv");
}

void skynet::load(const char*)
{

}

void skynet::save(const char*)
{

}

double skynet::normalize(double val) // normalizes a value by the normalization scalar and offset
{
	return val*normalizationScalar + offset;
}

double skynet::denormalize(double val) // denormalizes a value by the normalization scalar and offset
{
	return (val - offset) / normalizationScalar;
}

double skynet::learningRateFunction(double totalError, double learningRate)
{
	return exponent(totalError, learningRate);
}

double skynet::exponent(double error, double learningRate)
{
	return exp(error * learningRate) - 1;
}

double skynet::linear(double error, double learningRate)
{
	return error * learningRate;
}

double skynet::independant(double error, double learningRate)
{
	return learningRate; 
}