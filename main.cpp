#include "stockManager.h"

int main()
{
	char* sN[5] = { "ndaq",	"ko",	"dow", "k", "aapl" };
	int length = 1800, interval = 60, stockNumber = 5; //stock market hours are from 9:30am till 4:00pm total trading hours = 6:30 or 390 mins or 234000
	stockManager* sM;
	sM = new stockManager(length, interval, sN, stockNumber);
	bool initialized = sM->initialize();

	if(initialized == true)
	{
		sM->loop();
	}

	return 1;
}