#include "embeddedPython.h"

bool pyWeb::initialize()
{
	Py_Initialize();

	const char* name = {"anystock"}; //path
	const char* func = { "anyStock" }; //name of function
	PyObject* pName = PyString_FromString(name);
	pModule = PyImport_ImportModuleNoBlock(name);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, func);
		return true;
	}
	else {
		PyErr_Print();
		cout << "failed to load" << name << endl;
		return false;
	}
}

/*
double pyWeb::getValue(char* name)
{ 
	PyObject* pyStock = PyString_FromString("ko");

	cout << "name:" << PyString_AsString(pyStock) << "	size:" <<PyString_Size(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << temp << endl;
	return temp;
	
}*/