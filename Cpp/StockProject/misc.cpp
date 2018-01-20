#include "misc.h"

size_t stringToInt(string str)
{
   size_t num = 0;
   for (size_t i = 0; i < str.size(); i++)
   {
      short value = str[i] - '0';
      num = 10 * num + value;
   }
   return num;
}

bool stringToBool(string str)
{
   return (str[0] == '1' ? true : false);
}


double stringToDouble(string str)
{
   double num = 0;
   size_t decimalIndex = -1;
   int sign = 1;
   if (str[0] == '-')
   {
      sign = -1;
      str = str.substr(1, str.size());
   }
   for (size_t i = 0; i < str.size(); i++)
   {
      if (str[i] == '.')
      {
         decimalIndex = i;
         break;
      }
      short value = str[i] - '0';
      num = 10 * num + value;
   }

   int divisor = 10;
   for (size_t i = decimalIndex + 1; i < str.size(); i++)
   {
      short value = str[i] - '0';
      num += ((double)value / divisor);
      divisor *= 10;
   }

   return sign * num;
}