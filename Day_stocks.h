#include "Day_stocks.h"

Day_stocks::Day_stocks(const int numStocks, const int numValsStored)
{
   if (numStocks < MIN_NUM_STOCKS)
      this->numStocks = DEFAULT_NUM_STOCKS;
   else
      this->numStocks = numStocks;
   if (numValsStored < MIN_NUM_VALS_STORED || numValsStored > MAX_NUM_VALS_STORED)
      this->numValsStored = DEFAULT_NUM_VALS_STORED;
   else
      this->numValsStored = numValsStored;

   allocate();
}

void Day_stocks::allocate()
{
   Stocks = new double*[numStocks];
   for (int stock = 0; stock < numStocks; stock++)
      Stocks[stock] = new double[numValsStored];
}

void Day_stocks::deallocate()
{
   for (int stock = 0; stock < numStocks; stock++)
      delete[] Stocks[stock];
   delete[] Stocks;
}

bool Day_stocks::Save()
{
   ofstream stockFile;

   stockFile.open("Day", ios::out | ios::binary);
   if (!stockFile)
   {
      return false;
   }
   stockFile.write((char*)Stocks, sizeof(Stocks));
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
   stockFile.read((char*)Stocks, sizeof(Stocks));
   stockFile.close();
   return true;
}

void Day_stocks::printValues()
{
   for (int b = 0; b < numStocks; ++b)
   {
      for (int i = 0; i < numValsStored; ++i)
      {
         cout << " " << Stocks[b][i];
      }
      cout << "\n";
   }
}

bool Day_stocks::set(const int stockNumber, const int posToStore, const double val)
{
   if (stockNumber < 0 || stockNumber >= numStocks ||
      posToStore < 0 || posToStore >= numValsStored)
      throw Day_stocks::OutOfBoundsException();

   Stocks[stockNumber][posToStore] = val;
   return true;
}
