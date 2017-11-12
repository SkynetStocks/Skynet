#include "stockLoader.h"
#include <fstream>
#include <iostream>
#include "analysis.h"
#include "neuralNetwork\network.h"

using namespace std;

int main()
{
	stockLoader sL; // creates stock loading object
	sL.initialise();
	stockSampler* sS = sL.loadStock("KO", date_time(2003, 1, 1, 1, 1, 1), date_time(2017, 8, 10, 1, 1, 1)); //loads values from stock KO stores values in a stockSampler Object

	network skynet(10,1,3,11); //create network


	date_time startDate(2005, 1, 1, 1, 1, 1);
	date endDate = startDate.getDate();
	endDate.addDay(2);
	unsigned int sampleInterval = 20;
	endDate.addDay(sampleInterval);
	cout << "endDate:" << endDate.getYearI() << "," << endDate.getMonthUI() << "," << endDate.getDayUI() << endl;
	vector<double> inputs, output, actualOutput, outputAnalysis, actualOutputAnalysis;
	double uncertaintyOfOutput, error, normalizationFactor = 100;
	for (unsigned int i = 0; i < 200; ++i)
	{
		stockSampler* subSet = sS->getSubset(startDate, date_time(endDate, T::time(1, 1, 1)), 9, 1);
		inputs = subSet->getPointsd();
		//nomalization
		for (unsigned int b = 0; b < inputs.size(); ++b)
		{
			inputs[b] /= normalizationFactor;
		}
	
		output.push_back(sS->getValue(date_time(endDate, T::time(1, 1, 1)),uncertaintyOfOutput)/normalizationFactor);
		cout << "inputs:" << inputs.size() << endl;
		for (unsigned int i = 0; i < inputs.size(); ++i)
		{
			cout << inputs[i] << ",";
		}
		cout << endl << "output:" << output[0]*100 << endl;

		//do neural net shit
		skynet.assignInputs(inputs);
		actualOutput = skynet.getOutputs();
		actualOutputAnalysis.push_back(actualOutput[0]*100);
		outputAnalysis.push_back(output[0]*100);
		error = skynet.train(output, 0.1);
		cout << "computedOutput:" << actualOutput[0]*100 << endl;
		cout << "error:" << error*100 << endl << endl;

		delete subSet;
		output.clear();
		startDate.getDate().addDay(1);
		endDate.addDay(1);
	}

	vector<vector<double>> analysisData;
	analysisData.push_back(actualOutputAnalysis);
	analysisData.push_back(outputAnalysis);
	createCSV(analysisData, "data.csv");


	return 0;
}
