#include "date_time.h"


date_time::date_time()
{
}

date_time::date_time(int yVal, unsigned int moVal, unsigned int dVal, unsigned int hVal, unsigned int miVal, unsigned int sVal)
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

bool date_time::operator>(date_time const& val)
{
	if (d > val.getDate())
		return true;
	else if (t > val.getTime())
		return true;
	else
		return false;
}

bool date_time::operator<(date_time const& val)
{
	if (d < val.getDate())
		return true;
	else if (t < val.getTime())
		return true;
	else
		return false;
}

bool date_time::operator>=(date_time const& val)
{
	if (d >= val.getDate())
		return true;
	else if (t >= val.getTime())
		return true;
	else
		return false;
}

bool date_time::operator<=(date_time const& val)
{
	if (d <= val.getDate())
		return true;
	else if (t <= val.getTime())
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