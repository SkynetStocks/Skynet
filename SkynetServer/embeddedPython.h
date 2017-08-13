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
	double getValue(char* name);
private:
	PyObject *pModule, *pFunc; //pName = python script path 	pModule = python executable		pFunc = function to be called
};

#endif //EMBEDDEDPHYTHON_H