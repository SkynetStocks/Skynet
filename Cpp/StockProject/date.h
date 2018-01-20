#pragma once
#include "year.h"
#include "month.h"
#include "day.h"

class date
{
public:
	date();
	date(year yVal, month mVal, day dVal) :y(yVal),m(mVal),d(dVal) {};
	date(int yVal, unsigned int mVal, unsigned int dVal);//definition in cpp
	virtual ~date();
	
	//get
	inline year getYear() const{ return y; }
	inline month getMonth() const{ return m; }
	inline day getDay() const{ return d; }

	//fundamental data type get
	inline int getYearI() const{ return y.getYear(); }
	inline unsigned int getMonthUI() const{ return m.getMonth(); }
	inline unsigned int getDayUI() const{ return d.getDay(); }
	
	//set
	inline void setYear(year newY) { y = newY; }
	inline void setMonth(month newM) { m = newM; }
	inline void setDay(day newD) { d = newD; }
	inline void setYear(int newY) { y.setYear(newY); }
	inline void setMonth(unsigned int newM) { m.setMonth(newM); }
	inline void setDay(unsigned int newD) { d.setDay(newD); }

	//math
	void addYear(year yVal);
	void addMonth(month mVal);
	void addDay(day dVal);
	void addYear(int yVal);
	void addMonth(int mVal);
	void addDay(int dVal);

	//operator overloading

	//iterators
	date& operator++();

	//logic operators
	bool operator>(date const&);
	bool operator<(date const&);
	bool operator>=(date const&);
	bool operator<=(date const&);
	bool operator==(date const&);
	bool operator!=(date const&);

	unsigned int daysPerMonth(unsigned int mVal, int yVal);
private: 
	year y;
	month m;
	day d;
	bool isLeapYear(int yVal);
	unsigned int maxDays[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };//leap year feb, january, febuary, march, etc
};


