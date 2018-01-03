#include "skynet.h"

using namespace std;

int main()
{
	skynet networkMgr;
	cout << "initialising\n";
	if (!networkMgr.intitalise("KO", date_time(2003, 1, 1, 1, 1, 1), date_time(2017, 1, 1, 1, 1, 1), 100, 1, 3, 20))
	{
		cout << "failed to intialise\n";
		return -1;
	}

	cout << "training\n";

	vector<double> rms; //stores the root means squared of each run
	char buffer[255];




	rms = networkMgr.RTC(date_time(2004, 1, 1, 1, 1, 1), date_time(2011, 1, 1, 1, 1, 1), 6000, 20 * 60 * 60 * 24, 60 * 60 * 24, 0.05);
	
	networkMgr.run(date_time(2011, 1, 1, 1, 1, 1), date_time(2015, 1, 1, 1, 1, 1), 3000, 20 * 60 * 60 * 24, 60 * 60 * 24, "run.csv");
	

	vector<vector<double>> lRRms; //combines learning rate and rms, needs better name but well whatever

	lRRms.push_back(rms);
	
	createCSV(lRRms, "linearActivation.csv");



	return 0;
}