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

	double learningRate = 4;
	networkMgr.train(date_time(2004, 1, 1, 1, 1, 1), date_time(2006, 1, 1, 1, 1, 1),2000,20*60*60*24,60*60*24, learningRate);
	networkMgr.run(date_time(2006, 1, 1, 1, 1, 1), date_time(2010, 1, 1, 1, 1, 1), 2000, 20 * 60 * 60 * 24, 60 * 60 * 24);


	return 0;
}
