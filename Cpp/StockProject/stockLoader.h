#pragma once
#include "stockSampler.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>

#include "C:\Program Files\MySQL\Connector.C++ 1.1\include\mysql_connection.h"

#include <C:\Program Files\MySQL\Connector.C++ 1.1\include\cppconn\driver.h>
#include <C:\Program Files\MySQL\Connector.C++ 1.1\include\cppconn\exception.h>
#include <C:\Program Files\MySQL\Connector.C++ 1.1\include\cppconn\resultset.h>
#include <C:\Program Files\MySQL\Connector.C++ 1.1\include\cppconn\statement.h>
#include <C:\Program Files\MySQL\Connector.C++ 1.1\include\cppconn\prepared_statement.h>

#define skynetHost "localhost"
#define user "root"
#define userPwd "235711"
#define database "skynetserver"

class stockLoader
{
public:
	stockLoader();
	virtual ~stockLoader();
	bool initialise();
	stockSampler* loadStock(const char* stockName, date_time start, date_time end);
	stockSampler* loadStockVolume(const char* stockName, date_time start, date_time end);
private:
	sql::Driver *driver = nullptr;
	sql::Connection *con = nullptr;
	sql::Statement *stmt = nullptr;
	bool initialised;
};

