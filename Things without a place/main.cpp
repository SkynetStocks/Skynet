#include <iostream>
#include <fstream>
#include "stockLoader.h"

using namespace std;

vector<vector<stockNode>> getVectorOfData(date startDate, date endDate, size_t numDaysPerRow = 30);
void saveTrainingData(vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex);
void saveTestingData(vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex);

int main()
{
   vector<vector<stockNode>> allData = getVectorOfData(date(2016, 6, 7), date(2017, 5, 1));
   size_t threeFourthsPoint = (size_t)(3.0 * allData.size() / 4);
   saveTrainingData(allData, 0, threeFourthsPoint);
   saveTestingData(allData, threeFourthsPoint + 1, allData.size() - 1);
	return 0;
}

vector<vector<stockNode>> getVectorOfData(date startDate, date endDate, size_t numDaysPerRow)
{
   stockLoader sL; // creates stock loading object
   stockSampler* sS = sL.loadStock("KO"); //loads values from stock KO stores values in a stockSampler Object
   cout << endl << endl;
   stockSampler* subSet; //can make a subset of the values, stored as another sampler object
   vector<vector<stockNode>> allData;

   date currentStartDate(startDate.getYear(), startDate.getMonth(), startDate.getDay());
   date currentEndDate(startDate.getYear(), startDate.getMonth(), startDate.getDay());

   for (size_t i = 0; i < numDaysPerRow; i++)
      ++currentEndDate;

   for (; currentEndDate <= endDate; ++currentStartDate, ++currentEndDate)
   {
      subSet = sS->getSubset(
         date_time(
            currentStartDate.getYearI(),
            currentStartDate.getMonthUI(),
            currentStartDate.getDayUI(),
            1, 1, 1),
         date_time(
            currentEndDate.getYearI(),
            currentEndDate.getMonthUI(),
            currentEndDate.getDayUI(),
            1, 1, 1),
         24, 1);
      allData.push_back(subSet->getPoints());
   }

   delete sS;
   delete subSet;

   return allData;
}

void saveTrainingData(vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex)
{
   ofstream myfile;
   myfile.open("training-multisets.txt");

   size_t numData = endIndex - startIndex + 1;
   size_t numValuesPerDatum = allData[0].size() - 1;

   myfile << numData << "," << numValuesPerDatum;
   for (size_t i = startIndex; i <= endIndex; i++)
   {
      myfile << '\n';
      for (size_t j = 0; j < numValuesPerDatum; j++)
         myfile << allData[i][j].getValue() << ",";
      myfile << allData[i][numValuesPerDatum].getValue();
   }

   myfile.close();
}

void saveTestingData(vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex)
{
   ofstream myfile;
   myfile.open("testing-multisets.txt");

   size_t numData = endIndex - startIndex + 1;
   size_t numValuesPerDatum = allData[0].size() - 1;

   myfile << numData << "," << numValuesPerDatum;
   for (size_t i = startIndex; i <= endIndex; i++)
   {
      myfile << '\n';
      for (size_t j = 0; j < numValuesPerDatum; j++)
         myfile << allData[i][j].getValue() << ",";
      myfile << allData[i][numValuesPerDatum].getValue();
   }

   myfile.close();
}