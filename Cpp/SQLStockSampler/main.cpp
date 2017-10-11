#include "stockLoader.h"

int main()
{
	stockLoader sL; // creates stock loading object
	sL.initialise();
	stockSampler* sS = sL.loadStock("ko", date_time(2016, 1, 1, 1, 1, 1), date_time(2017, 7, 10, 1, 1, 1)); //loads values from stock KO stores values in a stockSampler Object
	cout << endl << endl;
	stockSampler* subSet = sS->getSubset(date_time(2016,1,1,1,1,1), date_time(2017,7,10,1,1,1),20, 1); //can make a subset of the values, stored as another sampler object
	//get volume
	stockSampler* volumeSet = sL.loadStockVolume("ko", date_time(2016, 1, 1, 1, 1, 1), date_time(2017, 7, 10, 1, 1, 1));
	stockSampler* volumeSubset = volumeSet->getSubset(date_time(2016, 1, 1, 1, 1, 1), date_time(2017, 7, 10, 1, 1, 1), 20, 1);

	vector<stockNode> stockPoints = subSet->getPoints(); // values of ko
	vector<stockNode> stockVolumePoints = volumeSubset->getPoints(); // volumes of ko



	delete sS;
	delete subSet;
	delete volumeSet;
	delete volumeSubset;
	return 1;
}