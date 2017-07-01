#pragma once
class month
{
public:
	month() {};
	month(unsigned int mVal) :m(mVal){};
	virtual ~month() {};

	//get
	inline unsigned int getMonth() const{ return m; }
	//set
	inline void setMonth(unsigned int newM) { m = newM; }

	//math
	inline void addMonth(unsigned int termM) { m += termM; }
	inline void addMonth(month termM) { m += termM.getMonth(); }

private:
	unsigned int m = 0;

private:

};

