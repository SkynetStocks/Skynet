#pragma once
#include "date.h"
#include "time.h"
#include <iostream>
using namespace std;
class date_time
{
public:
	date_time();
	date_time(date dVal, T::time tVal) :d(dVal), t(tVal) {};
	date_time(int yVal, int moVal, int dVal, int hVal, int miVal, int sVal);
	virtual ~date_time();

	//get
	inline date getDate() const{ return d; }
	inline T::time getTime() const{ return t; }
	inline year getYear() const { return d.getYear(); }
	inline month getMonth() const { return d.getMonth(); }
	inline day getDay() const { return d.getDay(); }
	inline hour getHour() const { return t.getHour(); }
	inline minute getMinute() const { return t.getMinute(); }
	inline second getSecond() const { return t.getSecond(); }

	inline int getYearI() const { return d.getYearI(); }
	inline unsigned int getMonthUI() const { return d.getMonthUI(); }
	inline unsigned int getDayUI() const { return d.getDayUI(); }
	inline int getHourI() const { return t.getHourI(); }
	inline int getMinuteI() const { return t.getMinuteI(); }
	inline int getSecondI() const { return t.getSecondI(); }

	//set
	inline void setDate(date newD) { d = newD; }
	inline void setTime(T::time newT) { t = newT; }

	//operator overloads

	//math
	int diffSeconds(date_time); //returns the difference in time in seconds
	void addSeconds(second); 

	//logic operators
	bool operator>(date_time const&);
	bool operator<(date_time const&);
	bool operator>=(date_time const&);
	bool operator<=(date_time const&);
	bool operator==(date_time const&);
	bool operator!=(date_time const&);

private:
	date d;
	T::time t;
};

