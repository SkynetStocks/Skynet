#ifndef EMBEDDEDPYTHON_H
#define EMBEDDEDPYTHON_H
#include <iostream>
#include "C:\Python27amd64\include\Python.h"
using namespace std;

class pyWeb
{
public:
	pyWeb() {};
	virtual ~pyWeb() { Py_Finalize(); };
	bool initialize();
	double getValue(char* name)
	{
			PyObject* pyStock = PyString_FromString(name);

			cout << "name:" << PyString_AsString(pyStock) << "	size:" << PyString_Size(pyStock) << endl;
			PyObject *pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, pyStock);
			PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
			if (pValue == NULL)
				cout << "shit has hit fan\n";
			double temp = PyFloat_AsDouble(pValue);
			cout << temp << endl;
			return temp;

	}
private:
	PyObject *pModule, *pFunc; //pName = python script path 	pModule = python executable		pFunc = function to be called
};

#endif //EMBEDDEDPHYTHON_H