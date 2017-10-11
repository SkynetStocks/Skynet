#pragma once
class second
{
public:
	second() {};
	second(int sVal) :s(sVal){};
	virtual ~second() {};

	//get
	inline int getSecond() const{ return s; }
	//set
	inline void setSecond(unsigned int newS) { s = newS; }

	//math
	inline void addSecond(int termS) { s += termS; }
	inline void addSecond(second termS) { s += termS.getSecond(); }
	inline void subSecond(int termS) { s -= termS; }
	inline void subSecond(second termS) { s -= termS.getSecond(); }

	//operators
	//math operators
	

private:
	int s = 0;
};

