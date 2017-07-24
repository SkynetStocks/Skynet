#pragma once
#include "date_time.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class stockNode
{
public:
	stockNode() {};
	stockNode(date_time dt, double val) :d(dt), stockVal(val){};
	stockNode(date_time dt, double val, double unVal) :d(dt), stockVal(val), uncertainty(unVal){};
	virtual ~stockNode() { if(next!=nullptr)delete next; }
	//get
	inline date_time getDate() const{ return d; }
	inline double getValue() const{ return stockVal; }
	inline stockNode* getNext() const{ return next; }
	inline double getUncertainty() const{ return uncertainty; }

	//set
	inline void setDate(date_time newD) { d = newD; }
	inline void setValue(double newVal) { stockVal = newVal; }
	inline void setNext(stockNode* newNext) { next = newNext; }
	inline void setUncertainty(double unVal) { uncertainty = unVal; }
private:
	stockNode* next = nullptr;

	date_time d; 
	double stockVal = 0;
	double uncertainty = 0;
};

//sorted list of stock values sorted via date, leas recent -> most recent
class stockSampler
{
public:
	stockSampler();
	virtual ~stockSampler();

	void insert(date_time, double, double);
	bool remove(date_time); //returns if entry exists or not
	double getValue(date_time, double& uncertainty); //returns a value with linear interpolation between points, the uncertainty is passed by reference to the user of the function via the parameter uncertainty
	void clear();//removes all entrys
	bool isEmpty() {return !pHead->getNext(); }
	stockSampler* getSubset(date_time start, date_time end, unsigned int sampleNumber, double slope);
	vector<stockNode> getPoints();
private:
	stockNode* pHead;//token head, no actuall value
};

