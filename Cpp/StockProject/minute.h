#pragma once
class minute
{
public:
	minute(){};
	minute(int mVal) :m(mVal){};
	virtual ~minute(){};

	//get
	inline int getMinute() const{ return m; }
	//set
	inline void setMinute(int newM) { m = newM; }
	
	//math
	inline void addMinute(int termM) { m += termM; }
	inline void addMinute(minute termM) { m += termM.getMinute(); }
	inline void subMinute(int termM) { m -= termM; }
	inline void subMinute(minute termM) { m -= termM.getMinute(); }

private:
	int m = 0;
};

