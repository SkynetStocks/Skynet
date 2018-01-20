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
	inline void addYear(year termY) { y += termY.getYear(); }

	//logic operators
	bool operator>(year const& val);
	bool operator<(year const& val);
	bool operator>=(year const& val);
	bool operator<=(year const& val);
	bool operator==(year const& val);
	bool operator!=(year const& val);

	bool operator>(unsigned int const& val);
	bool operator<(unsigned int const& val);
	bool operator>=(unsigned int const& val);
	bool operator<=(unsigned int const& val);
	bool operator==(unsigned int const& val);
	bool operator!=(unsigned int const& val);

private:
	int y = 0;

};

