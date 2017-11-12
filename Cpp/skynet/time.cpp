#include "time.h"


T::time::time()
{
}


T::time::~time()
{
}

void T::time::addHour(hour termH)
{
	h.addHour(termH.getHour());
}

void T::time::addMinute(minute termM)
{
	unsigned int hS = termM.getMinute() / 60;
	
	h.addHour(hS);
	m.addMinute(termM.getMinute() - hS*60);
}

void T::time::addSecond(second termS)
{
	//cout << "termS:" << termS.getSecond();
	s.addSecond(termS);
	//correct for if s>59
	if (s.getSecond() > 59)
	{
		unsigned int hS= s.getSecond() / (60*60);
		unsigned int mS = (s.getSecond() - (hS * 60*60)) / 60;
		unsigned int sS = s.getSecond() - hS * (60*60) - mS * 60; //dont judge the variable name
		//cout << "hs:" << hS << " mS:" << mS << " sS:" << sS << endl << endl;
		s.setSecond(sS);
		m.addMinute(mS);
		h.addHour(hS);
	}
}

void T::time::subHour(hour termH)
{
	h.subHour(termH);
}

void T::time::subMinute(minute termM)
{
	unsigned int hS = termM.getMinute() / 60;
	h.subHour(hS);
	m.subMinute(termM.getMinute() - hS * 60);
}

void T::time::subSecond(second termS)
{
	s.subSecond(termS);
	//correct for if s>59
	if (s.getSecond() < 0)
	{
		unsigned int hS = -s.getSecond() / 360;
		unsigned int mS = (-s.getSecond() - hS * 360) / 60;
		unsigned int sS = -s.getSecond()- hS * 360 - mS * 60; //dont judge the variable name; just the progammer
		s.setSecond(sS);
		m.subMinute(mS);
		h.subHour(hS);
	}
}

int T::time::timeDiffSec(time termT)
{
	time cpy = *this;
	cpy.subSecond(termT.getSecond());
	cpy.subMinute(termT.getMinute());
	cpy.subHour(termT.getHour()); //make cpy the difference in time between termT and this
	int val = cpy.getHourI() * 24 * 60 + cpy.getMinuteI() * 60 + cpy.getSecondI();
	return val;
}

//math operators
T::time T::time::operator+(time const& val)
{
	time sum = *this;
	sum.addSecond(val.getSecond());
	sum.addMinute(val.getMinute());
	sum.addHour(val.getHour());
	return sum;
}

T::time T::time::operator-(time const& val)
{
	time sub = *this;
	sub.subSecond(val.getSecond());
	sub.subMinute(val.getMinute());
	sub.subHour(val.getHour());
	return sub;
}

bool T::time::operator>(time const& val)
{
	if (h.getHour() > val.getHourI())
		return true;
	else if (m.getMinute() > val.getMinuteI())
		return true;
	else if (s.getSecond() > val.getSecondI())
		return true;
	else
		return false;
}

bool T::time::operator<(time const& val)
{
	if (h.getHour() < val.getHourI())
		return true;
	else if (m.getMinute() < val.getMinuteI())
		return true;
	else if (s.getSecond() < val.getSecondI())
		return true;
	else
		return false;
}

bool T::time::operator>=(time const& val)
{
	if (h.getHour() >= val.getHourI())
		return true;
	else if (m.getMinute() >= val.getMinuteI())
		return true;
	else if (s.getSecond() >= val.getSecondI())
		return true;
	else
		return false;
}

bool T::time::operator<=(time const& val)
{
	if (h.getHour() <= val.getHourI())
		return true;
	else if (m.getMinute() <= val.getMinuteI())
		return true;
	else if (s.getSecond() <= val.getSecondI())
		return true;
	else
		return false;
}

bool T::time::operator==(time const& val)
{
	if (h.getHour() == val.getHourI() && m.getMinute() == val.getMinuteI() && s.getSecond() == val.getSecondI())
		return true;
	else
		return false;
}

bool T::time::operator!=(time const& val)
{
	if (h.getHour() != val.getHourI() || m.getMinute() != val.getMinuteI() || s.getSecond() != val.getSecondI())
		return true;
	else
		return false;
}