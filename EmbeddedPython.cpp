#include <iostream>
#include <time.h>
#include <C:/Python27/include/Python.h>
#include "Day_stocks.h"

using namespace std;

const int TIME_INTERVAL_FOR_VALUE_GET = 3; // seconds
const int NUMBER_STOCKS = 1; // the number of stocks to store
const int NUMBER_VALUES_TO_STORE = 10;

/** This method takes a c-string and finds out how long it is.
MUST END IN A NULL CHARACTER (value of 0)
*/
int getArrSize(char *arr);
int beginCollectingAndSavingValues(char *stock, PyObject *pValue, PyObject *pFunc, PyObject *pArgs, PyObject *pModule);

/** argc = the number of white-space separated terms
argv = white-spaced separated c-strings
*/
int main(int argc, char *argv[])
{
   // Each of these is explained when it appears
   PyObject *pName, *pModule,/** *pDict, */ *pFunc;
   PyObject *pArgs, *pValue;
   //int i;       // USED AT THE COMMENT STUFF

   /** argc must have at least 3 values because:
   argv[0] = the program being executed
   argv[1] = the python module/script name
   argv[2] = the python method name
   argv[3], argv[4], argv[5],.... = the arguments/parameters for the python function
   */
   if (argc < 3) {
      fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
      return 1;
   }

   // This starts the python interpreter
   Py_Initialize();
   // pName holds the NAME (string) of the python module/script where the necessary method is defined
   pName = PyString_FromString(argv[1]);
   /* Error checking of pName left out */

   // pModule is the actual module that we need and it uses pName for its path
   pModule = PyImport_Import(pName);
   Py_DECREF(pName);

   // Making sure the module was found
   if (pModule != NULL) {
      // pFunc stores the method that we plan to call
      pFunc = PyObject_GetAttrString(pModule, argv[2]);
      /* pFunc is a new reference */

      // Making sure our function was found AND that it is callable
      if (pFunc && PyCallable_Check(pFunc)) {
         //----------NOT BEING USED FOR STOCK STUFFS--------------
         /*
         pArgs = PyTuple_New(argc - 3);
         for (i = 0; i < argc - 3; ++i) {
            pValue = PyInt_FromLong(atoi(argv[i + 3]));
            if (!pValue) {
               Py_DECREF(pArgs);
               Py_DECREF(pModule);
               fprintf(stderr, "Cannot convert argument\n");
               return 1;
            }
            /* pValue reference stolen here: */
            //PyTuple_SetItem(pArgs, i, pValue);
         //}
         //-------------------------------------------------------


         /** Choose one c-string to use then this segment of code will give it its own c-string (taken from argv[3] and placed in theStock)
         int arrSize = getArrSize(argv[3]);
         char *theStock = new char[arrSize];
         for (int j = 0; j < arrSize; j++)
         {
            char c = argv[3][j];
            if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
               break;
            theStock[j] = c;
         }
         */

         // the return value (exit code for the collector method)
         int returnValue = beginCollectingAndSavingValues(argv[3], pValue, pFunc, pArgs, pModule);
         if (returnValue == 1)
            return 1;

         //delete[] theStock;
      }
      else {
         if (PyErr_Occurred())
            PyErr_Print();
         fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
      }
      Py_XDECREF(pFunc);
      Py_DECREF(pModule);
   }
   else {
      PyErr_Print();
      fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
      return 1;
   }
   
   // Closing the Python interpreter
   Py_Finalize();
   
   /** THE PROGRAM IS NOT ENDING!!! I DO NOT KNOW WHAT IS HAPPENING!!! */

   return 0;
}

int getArrSize(char *arr)
{
   int arrSize = 0;
   int i = 0;
   while (arr[i] != 0)
   {
      i++;
      arrSize++;
   }
   return arrSize;
}

int beginCollectingAndSavingValues(char *stock, PyObject *pValue, PyObject *pFunc, PyObject *pArgs, PyObject *pModule)
{
   Day_stocks Stocks(NUMBER_STOCKS, NUMBER_VALUES_TO_STORE), newStocks(NUMBER_STOCKS, NUMBER_VALUES_TO_STORE);
   clock_t startTime, currentTime;
   int currentValueToStore = 0, timeIntervalMultiplier = 0;
   startTime = clock();

   // pArgs is our arguments for the python function, it has to be a PyTuple (I do not know what that is nor why)
   pArgs = PyTuple_New(1);
   //PyTuple_SetItem(pArgs, 0, PyString_FromStringAndSize(theStock, arrSize));
   PyTuple_SetItem(pArgs, 0, PyString_FromString(stock));

   do
   {
      currentTime = clock();
      double seconds = (currentTime - startTime) / (1.0 * CLOCKS_PER_SEC);
      if (seconds >= timeIntervalMultiplier * TIME_INTERVAL_FOR_VALUE_GET)
      {
         // pValue is whatever our python function returned
         pValue = PyObject_CallObject(pFunc, pArgs);
         //Py_DECREF(pArgs);
         // Making sure that we actually got something from the function call
         if (pValue != NULL) {
            //printf("Result of call: %ld\n", PyInt_AsLong(pValue));
            //printf("Result of call: %lf\n", PyFloat_AsDouble(pValue));
            Stocks.set(0, currentValueToStore++, PyFloat_AsDouble(pValue));
            Py_DECREF(pValue);
         }
         else {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            PyErr_Print();
            fprintf(stderr, "Call failed\n");
            return 1;
         }
         timeIntervalMultiplier++;
      }
   } while (currentValueToStore < NUMBER_VALUES_TO_STORE);
   Py_DECREF(pArgs);

   Stocks.Save();
   newStocks.Load();
   newStocks.printValues();

   return 0;
}
