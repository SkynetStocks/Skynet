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
	bool updateHtml(char* name);
	double getValue(char* name);
	double getVolume(char* name);
	double getRevenue(char* name);
	double getEmployeeNumber(char* name);
	double getIncome(char* name);
	//double getTinoTemp();
	//double getNYTemp();
private:
	PyObject *pAllDataModule, *pUpdateFunc, *pStockFunc ,*pVolFunc, *pRevFunc, *pEmpFunc, *pIncFunc;
};

#endif //EMBEDDEDPHYTHON_H