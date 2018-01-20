#pragma once
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

inline double MAX(double val1, double val2)
{
   return val1 > val2 ? val1 : val2;
}

inline double MIN(double val1, double val2)
{
   return val1 < val2 ? val1 : val2;
}


template <typename itemtype>
bool createCSV(vector<vector<itemtype>> data, const char* filename)
{
   ofstream file;
   file.open(filename);
   if (file)
   {
      unsigned int maxSize = 0;
      for (unsigned int i = 0; i < data.size(); ++i)
      {
         maxSize = MAX(data[i].size(), maxSize);
      }

      for (unsigned int i = 0; i < maxSize; ++i) // go down columns
      {
         for (unsigned int b = 0; b < data.size(); ++b) // go along rows
         {
            if (data[b].size() > i)
            {
               file << data[b][i] << ";";
            }
         }
         file << endl;
      }

      file.close();
      return true;
   }
   else
   {
      return false;
   }

}