#pragma once
#include "hour.h"
#include "minute.h"
#include "second.h"

class time
{
public:
	time();
	time(unsigned int hourValue, unsigned int minuteValue, unsigned int secondValue) :h(hourValue), m(minuteValue), s(secondValue) {};
	time(hour hourValue, minute minuteValue, second secondValue) :h(hourValue), m(minuteValue), s(secondValue) {};
	virtual ~time();

	//get
	inline hour getHour() const{ return h; }
	inline minute getMinute() const{ return m; }
	inline second getSecond() const{ return s; }

	//unsinged int get
	inline unsigned int getHourUI() const{ return h.getHour(); } 
	inline unsigned int getMinuteUI() const{ return m.getMinute(); }
	inline unsigned int getSecondUI() const{ return s.getSecond(); }

	/////////////////////////////////////////////////////////////////

	//set
	inline void setHour(hour newH) { h = newH; }
	inline void setMinute(minute newM) { m = newM; }
	inline void setSecond(second newS) { s = newS; }
	inline void setHour(unsigned int newH) { h.setHour(newH); }
	inline void setMinute(unsigned int newM) { m.setMinute(newM); }
	inline void setSecond(unsigned int newS) { s.setSecond(newS); }
	
	//math
	void addHour(hour termH);
	void addMinute(minute termM);
	void addSecond(second termS);

	//operator overloads

	//logic operators
	bool operator>(time const&);
	bool operator<(time const&);
	bool operator>=(time const&);
	bool operator<=(time const&);
	bool operator==(time const&);

private:
	hour h;
	minute m;
	second s;
};

