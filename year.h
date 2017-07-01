#pragma once
class year
{
public:
	year() {};
	year(unsigned int yVal) :y(yVal){};
	virtual ~year() {};

	//get
	inline int getYear() const{ return y; }
	//set
	inline void setYear(int newY) { y = newY; }

	//math
	inline void addYear(int termY) { y += termY; }
	inline void addMinute(year termY) { y += termY.getYear(); }

private:
	int y = 0;

};

