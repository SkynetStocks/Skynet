#include "stockManager.h"

stockManager::stockManager(int length, int interval, char* sN[], int numberOfStocks) :timeLength(length), timeInterval(interval)
{
	//initialize stock's
	for (int i = 0; i < numberOfStocks; ++i)
	{
		stockNames.push_back(sN[i]);
		Queue<double>* newQueue = new Queue<double>;
		dataPointers.push_back(newQueue);
	}
}

bool stockManager::initialize()
{
	if (webInterface.initialize() != true)
		return false;
	else
		return true;
}

void stockManager::loop()
{
	double value;
	for (int i = 0; i < timeLength / timeInterval; ++i)
	{
		for (int b = 0; b < dataPointers.size(); ++b)
		{
			 value = webInterface.getValue(stockNames[b]); //get stock values
			 dataPointers[i]->enqueue(value);
		}
		sleep_for(seconds(timeInterval)); //sleep for the time interval
		cout << i << endl;
	}


	//saveing block
	stockData sD(timeLength, timeInterval); 
	for (unsigned int i = 0; i < dataPointers.size(); ++i)
	{
		sD.setPtr(dataPointers[i]);
		string temp = to_string(i);
		sD.save(temp.c_str());
	}
}