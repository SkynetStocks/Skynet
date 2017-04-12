#include "Day_stocks.h"

int main()
{
	Day_stocks Stocks;
	Stocks.Save();
	Day_stocks newStocks;
	newStocks.Load();
	newStocks.printValues();
	return 1;
}