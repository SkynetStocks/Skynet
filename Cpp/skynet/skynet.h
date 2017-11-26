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
	void load(const char*); //saves the network as a file
	void save(const char*); //loads the network from a file
	void reset();
private:
	double normalize(double);
	double denormalize(double);
	double learningRateFunction(double totalError, double learningRate);

	//different learing rate functions
	double exponent(double error, double learningRate);
	double linear(double error, double learningRate);
	double independant(double error, double learningRate);

	network* net = nullptr;
	stockSampler* sS = nullptr;
	double normalizationScalar, offset;
};

