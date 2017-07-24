#pragma once
#include "stockSampler.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <fstream>

class stockLoader
{
public:
	stockLoader();
	virtual ~stockLoader();

	stockSampler* loadStock(const char* stockName);
private:
	bool stockDayExist(const char* name);
};

