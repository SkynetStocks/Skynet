#pragma once
#include <iostream>
#include <fstream>
#include "Queue.h"
using namespace std;

class stockData
{
public:

	stockData(int length, int interval) :timeLength(length), timeInterval(interval)
	{
			
	}

	virtual ~stockData()
	{
		
	}
	inline int getTimeLength() const{ return timeLength; }
	inline int getTimeInterval() const { return timeInterval; }
	inline void setPtr(Queue<double>* ptr) { pData = ptr; }
	bool save(const char* fileName);
	bool load(const char* fileName);
private:
	int timeLength, timeInterval; //both in seconds
	Queue<double>* pData; //pointer to the stock data
};