#include "stockLoader.h"
#include <fstream>
#include <iostream>
#include "analysis.h"
#include "neuralNetwork\network.h"
#pragma once
class skynet
{
public:
	skynet();
	virtual ~skynet();
	bool intitalise(const char* , date_time , date_time , unsigned int , unsigned int , unsigned int , unsigned int ); //initializes the network
	double train(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, double learningRate, const char* outputFile); //trains the network over a period of time, noItt is the number of times the network trains, subSampleLength & outputDistance is in seconds
	double run(date_time start, date_time end, unsigned int noItt, unsigned int subSampleLength, unsigned int outputDistance, const char* outputFile); //runs the network over a period of time, same as train function
	vector<double> RTC(date_time, date_time, unsigned int, unsigned int, unsigned int, double);//Run till convergance
	void load(const char*); //saves the network as a file
	void save(const char*); //loads the network from a file
	void reset();
private:
	void defineNormalizationValues();
	vector<double> assembleNetworkInput(date_time subStart, date_time subEnd);

	double valueNormalize(double);
	double valueDenormalize(double);
	double volumeNormalize(double);
	double volumeDenormalize(double);
	double nasdaqValueNormalize(double);
	double nasdaqVolumeNormalize(double);
	double dowjonesValueNormalize(double);
	double dowjonesVolumeNormalize(double);
	double sandpValueNormalize(double);
	double sandpVolumeNormalize(double);

	vector<unsigned int> intputDistribution(unsigned int noInputs);
	double learningRateFunction(double totalError, double learningRate);

	//different learing rate functions
	double exponent(double error, double learningRate);
	double linear(double error, double learningRate);
	double independant(double error, double learningRate);

	network* net = nullptr;
	stockSampler* sS = nullptr, * sV = nullptr;
	stockSampler* nasdaqValSamp = nullptr, *dowjonesValSamp = nullptr, *sandpValSamp = nullptr;
	stockSampler* nasdaqVolSamp = nullptr, *dowjonesVolSamp = nullptr, *sandpVolSamp = nullptr;

	double valueNormalizationScalar, valueNormalizationOffset;
	double volumeNormalizationScalar, volumeNormalizationOffset;

	double nasdaqValueNormalizationScalar, nasdaqValueNormalizationOffset = -1;
	double dowjonesValueNormalizationScalar, dowjonesValueNormalizationOffset = -1;
	double sandpValueNormalizationScalar, sandpValueNormalizationOffset = -1;

	double nasdaqVolumeNormalizationScalar, nasdaqVolumeNormalizationOffset = -1;
	double dowjonesVolumeNormalizationScalar, dowjonesVolumeNormalizationOffset = -1;
	double sandpVolumeNormalizationScalar, sandpVolumeNormalizationOffset = -1;
	vector<unsigned int> inputSections; //the number of inputs per type of input, such as stock, volume, nasdaq, etc
};

