#include "embeddedPython.h"

bool pyWeb::initialize()
{
	Py_Initialize();

	const char* aDName = { "allData" };
	const char* updateFunc = { "updateUrl" };
	const char* stockFunc = { "anyStock" };
	const char* volFunc = { "anyVolume" };
	const char* revFunc = { "anyRev" };
	const char* empFunc = { "anyEmp" };
	const char* incFunc = { "anyInc" };


	
	pAllDataModule = PyImport_ImportModuleNoBlock(aDName);

	if (pAllDataModule != NULL ) {

		//*pVolFunc, *pRevFunc, *pEmpFunc, *pIncFunc, *pTinoHumidFunc, *pTinoVisFunc, *pTinoWindFunc
		pUpdateFunc = PyObject_GetAttrString(pAllDataModule, updateFunc);
		pStockFunc = PyObject_GetAttrString(pAllDataModule, stockFunc);
		pVolFunc = PyObject_GetAttrString(pAllDataModule, volFunc);
		pRevFunc = PyObject_GetAttrString(pAllDataModule, revFunc);
		pEmpFunc = PyObject_GetAttrString(pAllDataModule, empFunc);
		pIncFunc = PyObject_GetAttrString(pAllDataModule, incFunc);


		return true;
	}
	else {
		PyErr_Print();
		return false;
	}
}

bool pyWeb::updateHtml(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* online = PyObject_CallObject(pUpdateFunc, pArgs);
	int check = PyInt_AsLong(online);
	cout << "check for web access:" << check << endl;
	if (check == -1) //if it was a successful update return with false
		return false;
	else
		return true;
}

double pyWeb::getValue(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	//cout << "name:" << PyString_AsString(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pStockFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "Value:" << temp << endl;
	return temp;

}


double pyWeb::getVolume(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	//cout << "name:" << PyString_AsString(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pVolFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "volume:" << temp << endl;
	return temp;
}

double pyWeb::getRevenue(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	//cout << "name:" << PyString_AsString(pyStock) << "	size:" << PyString_Size(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pRevFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "revenue:" << temp << endl;
	return temp;
}

double pyWeb::getEmployeeNumber(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	//cout << "name:" << PyString_AsString(pyStock) << "	size:" << PyString_Size(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pEmpFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "employee number:" << temp << endl;
	return temp;
}

double pyWeb::getIncome(char* name)
{
	PyObject* pyStock = PyString_FromString(name);

	//cout << "name:" << PyString_AsString(pyStock) << "	size:" << PyString_Size(pyStock) << endl;
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pyStock);
	PyObject* pValue = PyObject_CallObject(pIncFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "income:" << temp << endl;
	return temp;
}
/*
double pyWeb::getTinoTemp()
{
	PyObject *pArgs = PyTuple_New(0);
	PyObject* pValue = PyObject_CallObject(pTinoFunc,pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "tino temp:" << temp << endl;
	return temp;
}

double pyWeb::getNYTemp()
{
	PyObject *pArgs = PyTuple_New(0);
	PyObject* pValue = PyObject_CallObject(pNyFunc, pArgs);
	if (pValue == NULL)
		cout << "shit has hit fan\n";
	double temp = PyFloat_AsDouble(pValue);
	cout << "NyTemp:" << temp << endl;
	return temp;
}*/