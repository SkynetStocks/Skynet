#pragma once
class second
{
public:
	second() {};
	second(unsigned int sVal) :s(sVal){};
	virtual ~second() {};

	//get
	inline unsigned int getSecond() const{ return s; }
	//set
	inline void setSecond(unsigned int newS) { s = newS; }

	//math
	inline void addSecond(unsigned int termS) { s += termS; }
	inline void addSecond(second termS) { s += termS.getSecond(); }
private:
	unsigned int s = 0;
};

