#include "Day_stocks.h"

bool Day_stocks::Save()
{
	ofstream stockFile;

	for (int b = 0; b <= 1; ++b)  //give the stocks some values
	{
		for (int i = 0; i <= 9; ++i)
		{
			Stocks[b][i] = i + b;
		}
	}

	stockFile.open("Day", ios::out | ios::binary);
	if (!stockFile)
	{
		return false;
	}
	stockFile.write((char*)Stocks,sizeof(Stocks));
	stockFile.close();
	return true;
}

bool Day_stocks::Load()
{
	ifstream stockFile;
	stockFile.open("Day", ios::in | ios::binary);
	if (!stockFile)
	{
		return false;
	}
	stockFile.read((char*)Stocks,sizeof(Stocks));
	stockFile.close();
	return true;
}

void Day_stocks::printValues()
{
	for (int b = 0; b <= 1; ++b)
	{
		for (int i = 0; i <= 9; ++i)
		{
			cout << Stocks[b][i];
		}
		cout << "\n";
	}
}