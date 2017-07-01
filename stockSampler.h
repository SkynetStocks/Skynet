#pragma once
#include "date_time.h"

class stockNode
{
public:
	stockNode() {};
	stockNode(date_time dt, double val) :d(dt), stockVal(val){};
	virtual ~stockNode() {};
	//get
	inline date_time getDate() const{ return d; }
	inline double getValue() const{ return stockVal; }
	inline stockNode* getNext() const{ return next; }

	//set
	inline void setDate(date_time newD) { d = newD; }
	inline void setValue(double newVal) { stockVal = newVal; }
	inline void setNext(stockNode* newNext) { next = newNext; }
private:
	stockNode* next = nullptr;

	date_time d; 
	double stockVal = 0;
};

//sorted list of stock values sorted via date, leas recent -> most recent
class stockSampler
{
public:
	stockSampler();
	virtual ~stockSampler();

	void insert(date_time, double);
	bool remove(date_time); //returns if entry exists or not
	double getValue(date_time); //returns a value with linear interpolation between points
	void clear();//removes all entrys
private:
	stockNode* pHead;//token head, no actuall value
};

