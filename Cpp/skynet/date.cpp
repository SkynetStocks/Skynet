#include "date.h"


date::date() //zero value constructor
{
}

date::date(int yVal, unsigned int mVal, unsigned int dVal)
{
	y.setYear(yVal);
	m.setMonth(mVal);
	d.setDay(dVal);
}

date::~date()
{
}

//math

//

bool date::isLeapYear(int yVal)
{
	if (yVal % 4 == 0)
	{
		if (yVal % 100 == 0 || yVal % 400 == 0)
		{
			return true;
		}
		else if (yVal % 100 != 0)
		{
			return true;
		}
	}
	return false;
}

unsigned int date::daysPerMonth(unsigned int mVal, int yVal)
{
	if (isLeapYear(yVal) && mVal == 2) //if febuary and a leap year
	{
		return maxDays[0];
	}
	else
		return maxDays[mVal];
}

inline void date::addYear(year yVal)
{
	y.addYear(yVal);
}

inline void date::addMonth(month mVal)
{
	m.addMonth(mVal);
	if (m.getMonth() > 12)
	{
		int mS = m.getMonth() / 12; // number of years in the number of months
		y.addYear(mS);
		m.setMonth(m.getMonth() - m.getMonth() * 12);
		//correct for days
		while (d.getDay() > daysPerMonth(m.getMonth(), y.getYear())); 
		{
			d.setDay(d.getDay() - daysPerMonth(m.getMonth(), y.getYear())); 
			m.addMonth(1);
			if(m.getMonth() > 12)
			{
				m.setMonth(1);
				y.addYear(1);
			}
		}
	}
}

inline void date::addDay(day dVal)//suck a horse dick tom, love, jb
{
	d.addDay(dVal);
	//correct for a date that does not exist

	while (d.getDay() > daysPerMonth(m.getMonth(), y.getYear()))
	{
		d.setDay(d.getDay() - daysPerMonth(m.getMonth(), y.getYear()));
		m.addMonth(1);
		if (m.getMonth() > 12)
		{
			m.setMonth(1);
			y.addYear(1);
		}
	}
}

void date::addYear(int yVal)
{
	y.addYear(yVal);
}

void date::addMonth(int mVal)
{
	m.addMonth(mVal);
	if (m.getMonth() > 12)
	{
		int mS = m.getMonth() / 12; // number of years in the number of months
		y.addYear(mS);
		m.setMonth(m.getMonth() - m.getMonth() * 12);
		//correct for days
		while (d.getDay() > daysPerMonth(m.getMonth(), y.getYear()));
		{
			d.setDay(d.getDay() - daysPerMonth(m.getMonth(), y.getYear()));
			m.addMonth(1);
			if (m.getMonth() > 12)
			{
				m.setMonth(1);
				y.addYear(1);
			}
		}
	}
}

void date::addDay(int dVal)
{
	d.addDay(dVal);
	//correct for a date that does not exist
	//cout << "getDay:" << d.getDay() << endl;
	while (d.getDay() > daysPerMonth(m.getMonth(),y.getYear()))
	{
		
		d.setDay(d.getDay() - daysPerMonth(m.getMonth(), y.getYear()));
		m.addMonth(1);
		if (m.getMonth() > 12)
		{
			m.setMonth(1);
			y.addYear(1);
		}
	}
}

//operator

//iterators
date& date::operator++()
{
	//add 1 day
	//cout << d.getDay() << endl;
	d.addDay(1);
	//cout << d.getDay() << endl;
	//cout << daysPerMonth(m.getMonth(), y.getYear()) << endl;
	if (d.getDay() > daysPerMonth(m.getMonth(), y.getYear()))
	{
		d.setDay(1);
		m.addMonth(1);
		if (m.getMonth() > 12)
		{
			m.setMonth(1);
			y.addYear(1);
		}
	}
	return *this;
}

bool date::operator>(date const& otherDate)
{
	if (y.getYear() > otherDate.getYearI())
		return true;
	else if (m.getMonth() > otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else if (d.getDay() > otherDate.getDayUI() && m.getMonth() == otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else
		return false;
}

bool date::operator<(date const& otherDate)
{
	if (y.getYear() < otherDate.getYearI())
		return true;
	else if (m.getMonth() < otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else if (d.getDay() < otherDate.getDayUI() && m.getMonth() == otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else
		return false;
}

bool date::operator>=(date const& otherDate)
{
	if (*this == otherDate)
		return true;
	else if (y.getYear() > otherDate.getYearI())
		return true;
	else if (m.getMonth() > otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else if (d.getDay() > otherDate.getDayUI() && m.getMonth() == otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else
		return false;
}

bool date::operator<=(date const& otherDate)
{
	if (y.getYear() < otherDate.getYearI())
		return true;
	else if (m.getMonth() < otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else if (d.getDay() < otherDate.getDayUI() && m.getMonth() == otherDate.getMonthUI() && y.getYear() == otherDate.getYearI())
		return true;
	else
		return false;
}

bool date::operator==(date const& otherDate)
{
	if (otherDate.getYearI() == y.getYear() && otherDate.getMonthUI() == m.getMonth() && otherDate.getDayUI() == d.getDay())
		return true;
	else
		return false;
}

bool date::operator!=(date const& otherDate)
{
	if (otherDate.getYearI() != y.getYear() || otherDate.getMonthUI() != m.getMonth() || otherDate.getDayUI() != d.getDay())
		return true;
	else
		return false;
}
