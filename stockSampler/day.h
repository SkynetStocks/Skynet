#pragma once
#include <iostream>
using namespace std;
class day
{
public:
	day() {};
	day(unsigned int dVal) :d(dVal){};
	virtual ~day() {};

	//get
	inline unsigned int getDay() const{ return d; }
	//set
	inline void setDay(unsigned int newD){ d = newD; }

	inline void addDay(unsigned int termD) { d += termD; }
	inline void addDay(day termD) { d += termD.getDay(); }

	//logic operators
	bool operator>(day const& val);
	bool operator<(day const& val);
	bool operator>=(day const& val);
	bool operator<=(day const& val);
	bool operator==(day const& val);
	bool operator!=(day const& val);

	bool operator>(unsigned int const& val);
	bool operator<(unsigned int const& val);
	bool operator>=(unsigned int const& val);
	bool operator<=(unsigned int const& val);
	bool operator==(unsigned int const& val);
	bool operator!=(unsigned int const& val);

private:
	unsigned int d = 0;
};

