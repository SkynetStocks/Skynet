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
	bool quit = false;
	bool inHours = false;
	double value;
	time_t currentDay;
	struct tm currentTime;
	double MilitaryTime;
	stockData sD(timeLength, timeInterval);
	char name[255];

	while (!quit)
	{
		while (inHours)
		{
			for (int b = 0; b < dataPointers.size(); ++b)
			{
				value = webInterface.getValue(stockNames[b]); //get stock values
				dataPointers[b]->enqueue(value);
			}
			sleep_for(seconds(timeInterval)); //sleep for the time interval

			//test to see if in hours
			time(&currentDay);
			gmtime_s(&currentTime, &currentDay);
			MilitaryTime = abs(currentTime.tm_hour + float(currentTime.tm_min) / 100 - 4); //-8 acounts for time difference 
			if (MilitaryTime <= 9.3 || MilitaryTime > 16) //if not in opening times
			{
				inHours = false; //break while loop
				//save data
				cout << "saving" << endl;
				for (unsigned int i = 0; i < dataPointers.size(); ++i)
				{
					sD.setPtr(dataPointers[i]);
					//sprintf_s(name, "%s_%d/%d/%d", stockNames[i], currentTime.tm_mday, currentTime.tm_mon, currentTime.tm_year);
					sprintf_s(name, "%d-%d-%d_%s", currentTime.tm_year, currentTime.tm_mon, currentTime.tm_mday,stockNames[i]);
					cout <<"name:" << name << endl;
					sD.save(name);
					dataPointers[i]->clear();
				}

			}
		}

		//test to see if in hours
		time(&currentDay);
		gmtime_s(&currentTime, &currentDay);
		MilitaryTime = abs(currentTime.tm_hour + double(currentTime.tm_min) / 100 - 4); //-4 acounts for time difference, abs prevents negative time
		//cout <<"MilitaryTime:" << MilitaryTime << endl;
		if (MilitaryTime >= openTime && MilitaryTime <= closeTime)//if after opening time
		{
			inHours = true;
		}
		if (currentTime.tm_wday == 5 || currentTime.tm_wday == 6) //Off saturdays and sundays
		{
			inHours = false;
		}


		if(!inHours)
			sleep_for(seconds(10)); //wait for a minuit before testing again 
	}
}