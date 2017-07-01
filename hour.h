#pragma once
class hour
{
public:
	hour() {};
	hour(unsigned int hVal) :h(hVal){};
	virtual ~hour() {};

	//get
	inline unsigned int getHour() const{ return h; } // hour is in military time
	//set
	inline void setHour(unsigned int newH) { h = newH; }

	//math
	inline void addHour(unsigned int termH) { h += termH; }
	inline void addHour(hour termH) { h += termH.getHour(); }

private:
	unsigned int h = 0;
};

