#pragma once
class minute
{
public:
	minute(){};
	minute(unsigned int mVal) :m(mVal){};
	virtual ~minute(){};

	//get
	inline unsigned int getMinute() const{ return m; }
	//set
	inline void setMinute(unsigned int newM) { m = newM; }
	
	//math
	inline void addMinute(unsigned int termM) { m += termM; }
	inline void addMinute(minute termM) { m += termM.getMinute(); }

private:
	unsigned int m = 0;
};

