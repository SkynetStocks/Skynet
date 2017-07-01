#include "stockSampler.h"


stockSampler::stockSampler()
{
	pHead = new stockNode;
}


stockSampler::~stockSampler()
{
	clear();
}

void stockSampler::insert(date_time dt, double val)
{
	stockNode* newNode = new stockNode(dt, val);
	stockNode* itr = pHead; //iterator
	bool done = false;
	while (done == false) //until in correctly sorted position
	{
		if (itr->getNext() == nullptr)
			done = true;
		else if (itr->getNext()->getDate() > dt)
			done = true;
		else
			itr = itr->getNext(); //iterate
	}
	newNode->setNext(itr->getNext()); //insert into linked list
	itr->setNext(newNode);
}

bool stockSampler::remove(date_time dt)
{
	return false;
}

double stockSampler::getValue(date_time dt)
{
	return 0;
}

void stockSampler::clear()
{

}