#include "stockSampler.h"


stockSampler::stockSampler()
{
	pHead = new stockNode;
}


stockSampler::~stockSampler()
{
	delete pHead;//recursive delete in stockNode virtual destructor
}

void stockSampler::insert(date_time dt, double val, double un)
{
	//cout << "inserting value from date::" << dt.getYearI() << "," << dt.getMonthUI() << "," << dt.getDayUI() << "," << dt.getHourI() << "," << dt.getMinuteI() << "," << dt.getSecondI() << endl;
	stockNode* newNode = new stockNode(dt, val, un);
	stockNode* itr = pHead; //iterator
	bool done = false;
	while (done == false) //until in correctly sorted position
	{
		if (itr->getNext() == nullptr)
		{
			done = true;
			//cout << "end node\n";
		}
		else if (itr->getNext()->getDate() > dt)
		{
			done = true;
			//cout << "not end node\n";
		}
		else
			itr = itr->getNext(); //iterate
	}
	newNode->setNext(itr->getNext()); //insert into linked list
	itr->setNext(newNode);
}

bool stockSampler::remove(date_time dt)
{
	stockNode* itr = pHead;
	while (itr->getNext()->getDate() <= dt)
	{
		itr = itr->getNext();
	}
	if (itr->getNext()->getDate() == dt)
	{
		stockNode* temp = itr->getNext(); //if individual stock value exists we delete it
		itr->setNext(temp->getNext());
		delete temp;
		return true;
	}
	//if the stock point value does not exist return false to indicate it is not a node
	return false;
}

double stockSampler::getValue(date_time dt, double& uncertainty)//Linear interpolation as implementation
{
	stockNode* itr = pHead;
	bool done = false;
	while ( !done )
	{
		itr = itr->getNext();
		if (itr->getNext() == nullptr)
			done = true;
		else if (itr->getNext()->getDate() > dt)
			done = true;
	}
	if (itr->getNext() == nullptr)
	{
		//cout << "case 1\n";
		int diff = dt.diffSeconds(itr->getDate()); //distance from only known point use as uncertainty
		uncertainty = diff + itr->getUncertainty();
		return itr->getValue();
	}
	else if (itr->getNext()->getDate() == dt) //if date is a stockNode return value
	{
		//cout << "case 2\n";
		uncertainty = itr->getUncertainty(); //point exists so its uncertainty is of the node that gives it
		return itr->getValue();
	}
	else if (itr->getDate().getYearI() == 0) //if before the first valid node
	{
		//cout << "case 3\n";
		int diff = dt.diffSeconds(itr->getNext()->getDate()); //distance from only known point use as uncertainty
		uncertainty = diff + itr->getNext()->getUncertainty();
		return (itr->getNext()->getValue());
	}
	else  //linearly interpolate
	{
		//cout << "case 4\n";
		int diff1 = abs(dt.diffSeconds(itr->getDate()));
		//cout << "after diff 1\n";
		int diff2 = abs(dt.diffSeconds(itr->getNext()->getDate()));
		//cout << "start ifs\n";
		if (diff1 > diff2)
		{
			uncertainty = diff2 + (itr->getUncertainty()*diff1 + itr->getNext()->getUncertainty()*diff2) / (diff1 + diff2);
		}
		else
		{
			uncertainty = diff1 + (itr->getUncertainty()*diff1 + itr->getNext()->getUncertainty()*diff2) / (diff1 + diff2);
		}
		//cout << "about to return\n";
		return (itr->getValue()*diff1 + itr->getNext()->getValue()*diff2) / (diff1 + diff2);
	}
}

double stockSampler::getMaxValue()
{
	stockNode* itr = pHead;
	bool done = false;
	double maxVal = 0;
	while (!done)
	{
		maxVal = MAX(maxVal, itr->getValue());
		itr = itr->getNext();
		if (itr->getNext() == nullptr)
			done = true;
	}
	return maxVal;
}

double stockSampler::getMinValue()
{
	stockNode* itr = pHead;
	bool done = false;
	double maxVal = 0;
	while (!done)
	{
		maxVal = MIN(maxVal, itr->getValue());
		itr = itr->getNext();
		if (itr->getNext() == nullptr)
			done = true;
	}
	return maxVal;
}

void stockSampler::clear()
{
	delete pHead->getNext(); //recusivly implemented in stockNode destructor
}

stockSampler* stockSampler::getSubset(date_time start, date_time end, unsigned int sampleNumber, double slope)
{
	//cout << "Start Subset\n";
	stockSampler* newSample = new stockSampler();
	double samplePoint;
	date_time validSamplePoint;

	date_time zeroVal(start.getDate(), T::time(1, 1, 1));
	zeroVal.getDate().setYear(zeroVal.getDate().getYearI() - 1);
	int startSec = start.diffSeconds(zeroVal);
	int endSec = end.diffSeconds(zeroVal);
	//cout << "startSec:" << startSec << " endSec:" << endSec << endl;
	//cout << "secDiff:" << endSec - startSec << endl;

	double yIntercept = -slope*startSec;
	double area = slope*pow(endSec, 2) + yIntercept*endSec - slope*pow(startSec, 2) - yIntercept*startSec;
	double maxProbability = (slope*endSec + yIntercept); //probability at end point
	double stepSize = area / sampleNumber;
	//cout << "stepSize:" << stepSize << endl;
	//cout << "area:" << area << endl;
	//cout << "maxProbability:" << maxProbability << endl;
	//cout << "yIntercept:" << yIntercept << endl;
	//cout << (slope*endSec + yIntercept) << endl;
	//cout << (slope*startSec + yIntercept) << endl;

	double areaPos = stepSize/2;
	for (int i = 0; i <= sampleNumber; ++i)
	{
		//cout << "sample number:" << i << endl;
		//calculate point for sampling
		//cout << "areaPos:" << areaPos << endl;
		double c = -slope*pow(startSec, 2) - yIntercept*(startSec) -  areaPos;
		samplePoint = (-yIntercept + sqrt(pow(yIntercept, 2) - 4 * slope*c)) / (2 * slope);///quadratic formula
		areaPos += stepSize;

		samplePoint = ((samplePoint) - yIntercept)/slope;
		//cout << "sample Point:" << samplePoint << endl;
		validSamplePoint = zeroVal;
		//add number of seconds in sample point
		validSamplePoint.addSeconds(int(samplePoint));
		//cout << "y:" << validSamplePoint.getYearI() << " m:" << validSamplePoint.getMonthUI() << " d:" << validSamplePoint.getDayUI() << " h:" << validSamplePoint.getHourI() << " m:" << validSamplePoint.getMinuteI() << " s:" << validSamplePoint.getSecondI() << endl;
		double uncertainty;
		double value = getValue(validSamplePoint, uncertainty);
		//cout << "uncertainty:" << uncertainty << endl;
		newSample->insert(validSamplePoint,value, uncertainty);
	}
	//cout << "done";
	return newSample;
}

vector<stockNode> stockSampler::getPoints()
{
	vector<stockNode> values;
	bool done = false;
	if (isEmpty()) //if the stockSampler is empty return no values
	{
		//cout << "isEmpty\n";
		return values;
	}
	stockNode* itr = pHead->getNext();
	while (!done)
	{
		//cout << "next address:" << itr->getNext() << endl;
		//cout << "value:" << itr->getValue() << " uncertainty:" << itr->getUncertainty() << endl;
		values.push_back(stockNode(itr->getDate(), itr->getValue(), itr->getUncertainty()));
		if (itr->getNext() == nullptr)
			done = true;
		else
			itr = itr->getNext();
	}
	return values;
}

vector<double> stockSampler::getPointsd()
{
	vector<double> values;
	bool done = false;
	if (isEmpty()) //if the stockSampler is empty return no values
	{
		//cout << "is empty\n";
		return values;
	}
	stockNode* itr = pHead->getNext();
	while (!done)
	{
		//cout << "next address:" << itr->getNext() << endl;
		//cout << "value:" << itr->getValue() << " uncertainty:" << itr->getUncertainty() << endl;
		values.push_back(itr->getValue());
		if (itr->getNext() == nullptr)
			done = true;
		else
			itr = itr->getNext();
	}
	return values;
}