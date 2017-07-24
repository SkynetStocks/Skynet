#include "stockLoader.h"



stockLoader::stockLoader()
{
}


stockLoader::~stockLoader()
{
}

stockSampler* stockLoader::loadStock(const char* stockName)
{
	time_t currentDay;
	struct tm currentTime;
	char testFileName[255]; //file name to be tested for existance
	int timeInterval;
	int timeLength;
	stockSampler* sS = new stockSampler();

							//find start and end dates
	time(&currentDay);
	gmtime_s(&currentTime, &currentDay);
	date endItt = date( currentTime.tm_year - 100+2000, currentTime.tm_mon, currentTime.tm_mday); //end point for itterator
	date itt = date(2000, 1, 1);//when ever the stock market started, its a guess
	
	while (itt != endItt)
	{
		if (itt.getMonth() < 10 && itt.getDay() < 10)
		{
			sprintf_s(testFileName, "KO\\%d-0%d-0%d_%s", itt.getYearI(), itt.getMonthUI(), itt.getDayUI(), stockName);
		}
		else if (itt.getMonth() < 10)
		{
			sprintf_s(testFileName, "KO\\%d-0%d-%d_%s", itt.getYearI(), itt.getMonthUI(), itt.getDayUI(), stockName);
		}
		else if (itt.getDay() < 10)
		{
			sprintf_s(testFileName, "KO\\%d-%d-0%d_%s", itt.getYearI(), itt.getMonthUI(), itt.getDayUI(), stockName);
		}
		else
		{
			sprintf_s(testFileName, "KO\\%d-%d-%d_%s", itt.getYearI(), itt.getMonthUI(), itt.getDayUI(), stockName);
		}
		//std::cout << testFileName << "\n";
		if (stockDayExist(testFileName)) //test for files existance
		{
			//std::cout << "exists\n";
			std::ifstream stockFile(testFileName, std::ios::in | std::ios::binary);
			if (stockFile)
			{
				stockFile.read((char*)&timeInterval, sizeof(int));
				stockFile.read((char*)&timeLength, sizeof(int));
				//std::cout << "sampleNumber::" << timeInterval << std::endl;
				//std::cout << "timeLength::" << timeLength << std::endl;

				double dataPoint;
				T::time sampleTime = T::time (5, 30, 0);
				for (int i = 0; i <= timeLength ; i+= timeInterval)
				{
					//cout << "timeInterval:" << timeInterval << endl;
					//std::cout << "i::" << i << std::endl;
					stockFile.read(reinterpret_cast<char*>(&dataPoint), sizeof(double)); //there is a better way to write this, should change later down the line
					sS->insert(date_time(itt, sampleTime), dataPoint, 0);//insert value into list
					sampleTime.addSecond(timeInterval);
					//std::cout << "inserted::" << dataPoint << std::endl;
				}

				stockFile.close();
			}
			else
			{
				//std::cout << "stockFile failed to open\n";
			}
		}
		++itt;
	}
	return sS;
}

bool stockLoader::stockDayExist(const char* name)
{
	std::ifstream file(name);
	if (file.good())
		return true;
	else
		return false;
}