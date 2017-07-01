#pragma once
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

private:
	unsigned int d = 0;
};

