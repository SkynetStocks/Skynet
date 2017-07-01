#include "time.h"


time::time()
{
}


time::~time()
{
}

void time::addHour(hour termH)
{
	h.addHour(termH.getHour());
}

void time::addMinute(minute termM)
{
	h.addHour(termM.getMinute() / 60 );
	m.addMinute(termM.getMinute() - termM.getMinute() / 60);
}

void time::addSecond(second termS)
{
	s.addSecond(termS);
	//correct for if s>59
	if (s.getSecond() > 59)
	{
		unsigned int hS= s.getSecond() / 360;
		unsigned int mS = (s.getSecond() - hS * 360) / 60;
		unsigned int sS = s.getSecond() - hS * 360 - mS * 60; //dont judge the variable name
		s.setSecond(sS);
		m.addMinute(mS);
		h.addHour(hS);
	}
}

bool time::operator>(time const& val)
{
	if (h.getHour() > val.getHourUI())
		return true;
	else if (m.getMinute() > val.getMinuteUI())
		return true;
	else if (s.getSecond() > val.getSecondUI())
		return true;
	else
		return false;
}

bool time::operator<(time const& val)
{
	if (h.getHour() < val.getHourUI())
		return true;
	else if (m.getMinute() < val.getMinuteUI())
		return true;
	else if (s.getSecond() < val.getSecondUI())
		return true;
	else
		return false;
}

bool time::operator>=(time const& val)
{
	if (h.getHour() >= val.getHourUI())
		return true;
	else if (m.getMinute() >= val.getMinuteUI())
		return true;
	else if (s.getSecond() >= val.getSecondUI())
		return true;
	else
		return false;
}

bool time::operator<=(time const& val)
{
	if (h.getHour() <= val.getHourUI())
		return true;
	else if (m.getMinute() <= val.getMinuteUI())
		return true;
	else if (s.getSecond() <= val.getSecondUI())
		return true;
	else
		return false;
}

bool time::operator==(time const& val)
{
	if (h.getHour() == val.getHourUI() && m.getMinute() == val.getMinuteUI() && s.getSecond() == val.getSecondUI())
		return true;
	else
		return false;
}

