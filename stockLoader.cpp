#include "stockLoader.h"



stockLoader::stockLoader()
{
}


stockLoader::~stockLoader()
{
}

stockSampler stockLoader::loadStock(const char* stockName)
{
	time_t currentDay;
	struct tm currentTime;
	char testFileName[255]; //file name to be tested for existance

							//find start and end dates
	time(&currentDay);
	gmtime_s(&currentTime, &currentDay);
	for ( int y = 0; y <= (currentTime.tm_year - 100); ++y)
	{
		sprintf_s(testFileName, "%s/%d-01-01_%s", stockName, y + 2000, stockName);
		cout << testFileName << endl;
		if (stockDayExist(testFileName) == true)
			cout << "Yay!" << endl;
		else
			cout << "Shit!" << endl;
	}


}

bool stockLoader::stockDayExist(const char* name)
{
	ifstream file(name);
	if (file.good())
		return true;
	else
		return false;
}