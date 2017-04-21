#include <iostream>
#include <C:/Python27/include/Python.h>

using namespace std;

int main(int argc, char *argv[])
{
   PyObject *pName, *pModule,/** *pDict, */ *pFunc;
   PyObject *pArgs, *pValue;
   //int i;       // USED AT THE COMMENT STUFF

   if (argc < 3) {
      fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
      return 1;
   }

   Py_Initialize();
   pName = PyString_FromString(argv[1]);
   /* Error checking of pName left out */

   pModule = PyImport_Import(pName);
   Py_DECREF(pName);

   if (pModule != NULL) {
      pFunc = PyObject_GetAttrString(pModule, argv[2]);
      /* pFunc is a new reference */

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

         int arrSize = 0;
         int i = 0;
         while (argv[3][i] != 0)
         {
            i++;
            arrSize++;
         }
         char *theStock = new char[arrSize];
         for (int j = 0; j < arrSize; j++)
         {
            char c = argv[3][j];
            if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
               break;
            theStock[j] = c;
         }

         pArgs = PyTuple_New(1);
         PyTuple_SetItem(pArgs, 0, PyString_FromStringAndSize(theStock, arrSize));

         pValue = PyObject_CallObject(pFunc, pArgs);
         Py_DECREF(pArgs);
         if (pValue != NULL) {
            //printf("Result of call: %ld\n", PyInt_AsLong(pValue));
            printf("Result of call: %lf\n", PyFloat_AsDouble(pValue));
            Py_DECREF(pValue);
         }
         else {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            PyErr_Print();
            fprintf(stderr, "Call failed\n");
            return 1;
         }



         delete[] theStock;
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
   Py_Finalize();
   return 0;
}
