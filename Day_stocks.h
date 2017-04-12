#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Day_stocks
{
public:

	Day_stocks()
	{
	}

	virtual ~Day_stocks()
	{
	}

	bool Save(); //saves the Days stocks to a binary file
	bool Load(); //loads the Days stocks from a binary file
	void printValues(); //couts the stock values
private:
	double Stocks[2][10]; //
};

