#include "stockLoader.h"



stockLoader::stockLoader()
{
}


stockLoader::~stockLoader()
{
}

bool stockLoader::initialise()
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(skynetHost, user, userPwd);
		con->setSchema(database);
		stmt = con->createStatement();
		initialised = true;
	}
	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		// what() (derived from std::runtime_error) fetches error message 
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return false;
	}
}

stockSampler* stockLoader::loadStock(const char* stockName, date_time start, date_time end)
{
	if (initialised)
	{
		stockSampler* sample = new stockSampler;

		char statementString[400];
		string pointdatetime;
		double value;
		char temp[5]; //used to transfer from string to date_time
		size_t length;

		sprintf_s(statementString, "select * from %svalues WHERE pointdatetime >= '%.4d-%.2d-%.2d %.2d:%.2d:%.2d' AND pointdatetime <= '%.4d-%.2d-%.2d %.2d:%.2d:%.2d'", stockName, start.getYearI(), start.getMonthUI(), start.getDayUI(), start.getHourI(), start.getMinuteI(), start.getSecondI(), end.getYearI(), end.getMonthUI(), end.getDayUI(), end.getHourI(), end.getMinuteI(), end.getSecondI()); //check if date value already exists
		cout << "statementString:" << statementString << endl;

		try
		{
			sql::PreparedStatement* pstmt = con->prepareStatement(statementString);
			sql::ResultSet* res = pstmt->executeQuery();

			while (res->next()) //while there are still entries
			{
				value = res->getDouble("value");							//get values from sql entries
				pointdatetime = res->getString("pointdatetime").c_str();
				//convert string to date_time
				
				date_time entrypoint; //;D

				length = pointdatetime.copy(temp, 4, 0); // convert year
				temp[length] = '\0';
				entrypoint.setYear(atoi(temp));

				length = pointdatetime.copy(temp, 2, 5); // convert month
				temp[length] = '\0';
				entrypoint.setMonth(atoi(temp));

				length = pointdatetime.copy(temp, 2, 8); // convert day
				temp[length] = '\0';
				entrypoint.setDay(atoi(temp));

				length = pointdatetime.copy(temp, 2, 11); // convert hour
				temp[length] = '\0';
				entrypoint.setHour(atoi(temp));

				length = pointdatetime.copy(temp, 2, 14); // convert minute
				temp[length] = '\0';
				entrypoint.setMinute(atoi(temp));

				length = pointdatetime.copy(temp, 2, 17); // convert second
				temp[length] = '\0';
				entrypoint.setSecond(atoi(temp));

				//cout << entrypoint.getYearI() << "," << entrypoint.getMonthUI() << "," << entrypoint.getDayUI() << "," << entrypoint.getHourI() << "," << entrypoint.getMinuteI() << "," << entrypoint.getSecondI() << endl;

				sample->insert(entrypoint, value, 0);

			}

			delete pstmt;
			delete res;
		}
		catch (sql::SQLException &e)
		{
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			// what() (derived from std::runtime_error) fetches error message 
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		return sample;
	}
	return nullptr;
}

stockSampler* stockLoader::loadStockVolume(const char* stockName, date_time start, date_time end)
{

	if (initialised)
	{
		stockSampler* sample = new stockSampler;

		char statementString[400];
		string pointdatetime;
		double value;
		char temp[5]; //used to transfer from string to date_time
		size_t length;

		sprintf_s(statementString, "select * from %svolumes WHERE pointdatetime >= '%.4d-%.2d-%.2d %.2d:%.2d:%.2d' AND pointdatetime <= '%.4d-%.2d-%.2d %.2d:%.2d:%.2d'", stockName, start.getYearI(), start.getMonthUI(), start.getDayUI(), start.getHourI(), start.getMinuteI(), start.getSecondI(), end.getYearI(), end.getMonthUI(), end.getDayUI(), end.getHourI(), end.getMinuteI(), end.getSecondI()); //check if date value already exists
		cout << "statementString:" << statementString << endl;

		try
		{
			sql::PreparedStatement* pstmt = con->prepareStatement(statementString);
			sql::ResultSet* res = pstmt->executeQuery();

			while (res->next()) //while there are still entries
			{
				value = res->getDouble("volume");							//get values from sql entries
				pointdatetime = res->getString("pointdatetime").c_str();
				//convert string to date_time

				date_time entrypoint; //;D

				length = pointdatetime.copy(temp, 4, 0); // convert year
				temp[length] = '\0';
				entrypoint.setYear(atoi(temp));

				length = pointdatetime.copy(temp, 2, 5); // convert month
				temp[length] = '\0';
				entrypoint.setMonth(atoi(temp));

				length = pointdatetime.copy(temp, 2, 8); // convert day
				temp[length] = '\0';
				entrypoint.setDay(atoi(temp));

				length = pointdatetime.copy(temp, 2, 11); // convert hour
				temp[length] = '\0';
				entrypoint.setHour(atoi(temp));

				length = pointdatetime.copy(temp, 2, 14); // convert minute
				temp[length] = '\0';
				entrypoint.setMinute(atoi(temp));

				length = pointdatetime.copy(temp, 2, 17); // convert second
				temp[length] = '\0';
				entrypoint.setSecond(atoi(temp));

				//cout << "point" << entrypoint.getYearI() << "," << entrypoint.getMonthUI() << "," << entrypoint.getDayUI() << "," << entrypoint.getHourI() << "," << entrypoint.getMinuteI() << "," << entrypoint.getSecondI() << endl;
				//cout << value << endl;


				sample->insert(entrypoint, value, 0);

			}

			delete pstmt;
			delete res;
		}
		catch (sql::SQLException &e)
		{
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			// what() (derived from std::runtime_error) fetches error message 
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		return sample;
	}
	return nullptr;
}