#include "date_time.h"


date_time::date_time()
{
}

date_time::date_time(int yVal, int moVal, int dVal, int hVal, int miVal, int sVal)
{
	d.setYear(yVal);
	d.setMonth(moVal);
	d.setDay(dVal);
	t.setHour(hVal);
	t.setMinute(miVal);
	t.setSecond(sVal);
}

date_time::~date_time()
{
}

//math
int date_time::diffSeconds(date_time val) //implementation is crap, new method desired
{
	date_time itt;
	date_time end;
	unsigned int diffDays = 0;
	int diffTime;
	if (val >= *this)//get smallest date
	{
		//cout << "Case 1" << endl;
		itt = *this;
		end = val;
	}
	else
	{
		//cout << "Case 2" << endl;
		itt = val;
		end = *this;
	}
	diffTime = itt.t.timeDiffSec(end.getTime());
	//cout << "diffTime::" << diffTime << endl;
	//cout << "Itt y:" << itt.getYearI() << " m:" << itt.getMonthUI() << " d:" << itt.getDayUI() << endl;
	//cout << "End y:" << end.getYearI() << " m:" << end.getMonthUI() << " d:" << end.getDayUI() << endl;
	while (itt.d != end.d) //count difference in days
	{
		//cout << "days difference:" << diffDays << endl;
		//cout << "Itt y:" << itt.getYearI() << " m:" << itt.getMonthUI() << " d:" << itt.getDayUI() << endl;
		//cout << "End y:" << end.getYearI() << " m:" << end.getMonthUI() << " d:" << end.getDayUI() << endl;
		++diffDays;
		++itt.d;

	}
	return diffDays * 24 * 60 * 60 + diffTime;
}

void date_time::addSeconds(second sVal) //better method needed
{
	unsigned int daysToBeAdded = sVal.getSecond() / (60 * 60 * 24);
	for (unsigned int i = 0; i < daysToBeAdded; ++i)
	{
		++d;
	}
	//cout << "sVal:" << sVal.getSecond() << endl;
	//cout << "seconds to be added to time:" << sVal.getSecond() - daysToBeAdded * 60 * 60 * 24 << endl;
	t.addSecond(sVal.getSecond() - daysToBeAdded * 60 * 60 * 24);
	if (t.getHourI() >= 24)
	{
		daysToBeAdded = t.getHourI() / 24;
		for (unsigned int i = 0; i < daysToBeAdded; ++i)
		{
			++d;
		}
		t.setHour(t.getHourI() - 24 * daysToBeAdded);
	}
	//cout << "done adding days and seconds\n";
}

void date_time::addDays(unsigned int val)
{
	for (unsigned int i = 0; i < val; ++i)
	{
		++d;
	}
}

//operators

//logical operators

bool date_time::operator>(date_time const& val)
{
	if (d > val.getDate())
		return true;
	else if (t > val.getTime() && d == val.getDate())
		return true;
	else
		return false;
}

bool date_time::operator<(date_time const& val)
{
	if (d < val.getDate())
		return true;
	else if (t < val.getTime() && d == val.getDate())
		return true;
	else
		return false;
}

bool date_time::operator>=(date_time const& val)
{
	if (d >= val.getDate())
		return true;
	else if (t >= val.getTime() && d == val.getDate())
		return true;
	else
		return false;
}

bool date_time::operator<=(date_time const& val)
{
	if (d <= val.getDate())
		return true;
	else if (t <= val.getTime() && d == val.getDate())
		return true;
	else
		return false;
}

bool date_time::operator==(date_time const& val)
{
	if (val.getDate() == d && val.getTime() == t)
		return true;
	else
		return false;
}

bool date_time::operator!=(date_time const& val)
{
	if (val.getDate() != d || val.getTime() != t)
		return true;
	else
		return false;
}