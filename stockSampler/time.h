#pragma once
#include "hour.h"
#include "minute.h"
#include "second.h"
#include <iostream>
using namespace std;
namespace T {
	class time
	{
	public:
		time();
		time(int hourValue, int minuteValue, int secondValue) :h(hourValue), m(minuteValue), s(secondValue) {};
		time(hour hourValue, minute minuteValue, second secondValue) :h(hourValue), m(minuteValue), s(secondValue) {};
		virtual ~time();

		//get
		inline hour getHour() const { return h; }
		inline minute getMinute() const { return m; }
		inline second getSecond() const { return s; }

		//unsinged int get
		inline int getHourI() const { return h.getHour(); }
		inline int getMinuteI() const { return m.getMinute(); }
		inline int getSecondI() const { return s.getSecond(); }

		/////////////////////////////////////////////////////////////////

		//set
		inline void setHour(hour newH) { h = newH; }
		inline void setMinute(minute newM) { m = newM; }
		inline void setSecond(second newS) { s = newS; }
		inline void setHour(int newH) { h.setHour(newH); }
		inline void setMinute(int newM) { m.setMinute(newM); }
		inline void setSecond(int newS) { s.setSecond(newS); }

		//math
		void addHour(hour termH);
		void addMinute(minute termM);
		void addSecond(second termS);
		void subHour(hour termH);
		void subMinute(minute termM);
		void subSecond(second termM);
		int timeDiffSec(time);

		//operator overloads

		//math operators
		time operator+(time const&);
		time operator-(time const&);

		//logic operators
		bool operator>(time const&);
		bool operator<(time const&);
		bool operator>=(time const&);
		bool operator<=(time const&);
		bool operator==(time const&);
		bool operator!= (time const&);

	private:
		hour h;
		minute m;
		second s;
	};

}