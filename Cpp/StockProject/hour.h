#pragma once
class hour
{
public:
	hour() {};
	hour(int hVal) :h(hVal){};
	virtual ~hour() {};

	//get
	inline int getHour() const{ return h; } // hour is in military time
	//set
	inline void setHour(int newH) { h = newH; }

	//math
	inline void addHour(int termH) { h += termH; }
	inline void addHour(hour termH) { h += termH.getHour(); }
	inline void subHour(int termH) { h -= termH; }
	inline void subHour(hour termH) { h -= termH.getHour(); }

private:
	int h = 0;
};

