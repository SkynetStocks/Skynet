#pragma once
#include "date.h"
#include "time.h"
class date_time
{
public:
	date_time();
	date_time(date dVal, time tVal) :d(dVal), t(tVal) {};
	date_time(int yVal, unsigned int moVal, unsigned int dVal, unsigned int hVal, unsigned int miVal, unsigned int sVal);
	virtual ~date_time();

	//get
	inline date getDate() const{ return d; }
	inline time getTime() const{ return t; }

	//set
	inline void setDate(date newD) { d = newD; }
	inline void setTime(time newT) { t = newT; }

	//operator overloads

	//logic operators
	bool operator>(date_time const&);
	bool operator<(date_time const&);
	bool operator>=(date_time const&);
	bool operator<=(date_time const&);
	bool operator==(date_time const&);

private:
	date d;
	time t;
};

