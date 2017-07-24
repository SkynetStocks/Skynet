#include "stockLoader.h"

int main()
{
	stockLoader sL; // creates stock loading object
	stockSampler* sS = sL.loadStock("KO"); //loads values from stock KO stores values in a stockSampler Object
	cout << endl << endl;
	stockSampler* subSet = sS->getSubset(date_time(2016,1,1,1,1,1), date_time(2017,7,10,1,1,1),20, 1); //can make a subset of the values, stored as another sampler object
	vector<stockNode> stockPoints = subSet->getPoints();


	delete sS;
	delete subSet;
	return 1;
}