#pragma once
#include "stockData.h"
#include "embeddedPython.h"
#include "Queue.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
using namespace std::this_thread;
using namespace std::chrono;

class stockManager
{
public:

	stockManager(int length, int interval, char* sN[], int numberOfStocks);

	virtual ~stockManager()
	{
	}

	bool initialize();
	void loop(); //loops through the set time period and saves the files at the end

private:
	int timeLength, timeInterval; //in seconds
	double openTime = 9.3;
	double closeTime = 16;
	vector<char*> stockNames;
	vector<Queue<double>*> dataPointers; //pointers to stock data arrays
	pyWeb webInterface;
};

