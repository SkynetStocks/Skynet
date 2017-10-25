#include "stockLoader.h"
#include <fstream>

vector<vector<stockNode>> getVectorOfData(date startDate, date endDate, size_t numDaysPerRow = 30);
void saveData(const string name, vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex);

int main()
{ 
   vector<vector<stockNode>> allData = getVectorOfData(date(2016, 6, 7), date(2017, 5, 1), 30);
   size_t sixtyPercentPoint = (size_t)(3.0 * allData.size() / 5);
   saveData("training-multisets.txt", allData, 0, sixtyPercentPoint);
   saveData("testing-multisets.txt", allData, sixtyPercentPoint + 1, allData.size() - 1);

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
         numDaysPerRow, 1);
      allData.push_back(subSet->getPoints());
   }

   delete sS;
   delete subSet;

   return allData;
}

void saveData(const string name, vector<vector<stockNode>> allData, size_t startIndex, size_t endIndex)
{
   ofstream myfile;
   myfile.open(name);

   const size_t TOTAL_NUM_DATA = endIndex - startIndex + 1;
   const size_t NUM_VALUES_PER_DATUM = allData[0].size() - 1;
   const size_t NUM_VALUES_PER_LABEL = 1;

   myfile << TOTAL_NUM_DATA << "," << NUM_VALUES_PER_DATUM << "," << NUM_VALUES_PER_LABEL;
   for (size_t i = startIndex; i <= endIndex; i++)
   {
      myfile << '\n';
      for (size_t j = 0; j < NUM_VALUES_PER_DATUM; j++)
      {
         myfile << allData[i][j].getValue() << ','; // replace with open value
         // myfile << allData[i][j].getClosingValue() << ',';
         // myfile << allData[i][j].getHighValue() << ',';
         // myfile << allData[i][j].getLowValue();
         if (j < NUM_VALUES_PER_DATUM - 1)
            myfile << ',';
         else
            myfile << '\n';
      }

      double last = allData[i][NUM_VALUES_PER_DATUM].getValue();
      myfile << last;
   }

   myfile.close();
}
