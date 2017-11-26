#include "skynet.h"

using namespace std;

int main()
{
	skynet networkMgr;
	cout << "initialising\n";
	if (!networkMgr.intitalise("KO", date_time(2003, 1, 1, 1, 1, 1), date_time(2017, 1, 1, 1, 1, 1), 20, 1, 3, 11))
	{
		cout << "failed to intialise\n";
		return -1;
	}

	cout << "training\n";

	vector<double> rms; //stores the root means squared of each run
	char buffer[255];

	for (unsigned int i = 0; i < 100; ++i)
	{
		sprintf_s(buffer, "testData_%d.csv", i);
		networkMgr.train(date_time(2004, 1, 1, 1, 1, 1), date_time(2015, 1, 1, 1, 1, 1), 4000, 20 * 60 * 60 * 24, 60 * 60 * 24, 0.1, "delete");
		rms.push_back(networkMgr.train(date_time(2004, 1, 1, 1, 1, 1), date_time(2015, 1, 1, 1, 1, 1), 4000, 20 * 60 * 60 * 24, 60 * 60 * 24, 0.1, buffer));
		networkMgr.reset();
	}

	vector<vector<double>> lRRms; //combines learning rate and rms, needs better name but well whatever
	//lRRms.push_back(lR);
	lRRms.push_back(rms);
	createCSV(lRRms, "exponentialSampling.csv");



	return 0;
}