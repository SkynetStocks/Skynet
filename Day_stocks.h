#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Day_stocks
{
public:
   static const int DEFAULT_NUM_STOCKS = 2;
   static const int MIN_NUM_STOCKS = 1;

   static const int DEFAULT_NUM_VALS_STORED = 10;
   static const int MIN_NUM_VALS_STORED = 1;
   static const int MAX_NUM_VALS_STORED = 1000 * 1000 * 1000;

private:
   int numStocks;  // the number of stocks being stored (if NASDAQ, KO, AAPL then this value is 3)
   int numValsStored; // the number of values being stored per stock
   double **Stocks;

public:

   Day_stocks(const int numStocks = DEFAULT_NUM_STOCKS,
      const int numValsStored = DEFAULT_NUM_VALS_STORED);
   virtual ~Day_stocks() { deallocate(); }

   bool Save(); //saves the Days stocks to a binary file
   bool Load(); //loads the Days stocks from a binary file
   void printValues(); //couts the stock values

   bool set(const int stockNumber, const int posToStore, const double val);

   class OutOfBoundsException {};

private:
   void allocate();
   void deallocate();
};
