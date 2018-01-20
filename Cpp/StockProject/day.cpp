#include "day.h"

//logic operators
bool day::operator>(day const& val)
{
	if (d > val.getDay())
		return true;
	else
		return false;
}

bool day::operator<(day const& val)
{
	if (d < val.getDay())
		return true;
	else
		return false;
}

bool day::operator>=(day const& val)
{
	if (d >= val.getDay())
		return true;
	else
		return false;
}

bool day::operator<=(day const& val)
{
	if (d <= val.getDay())
		return true;
	else
		return false;
}

bool day::operator==(day const& val)
{
	if (d == val.getDay())
		return true;
	else
		return false;
}

bool day::operator!=(day const& val)
{
	if (d != val.getDay())
		return true;
	else
		return false;
}


bool day::operator>(unsigned int const& val)
{
	if (d > val)
		return true;
	else
		return false;
}

bool day::operator<(unsigned int const& val)
{
	if (d < val)
		return true;
	else
		return false;
}

bool day::operator>=(unsigned int const& val)
{
	if (d >= val)
		return true;
	else
		return false;
}

bool day::operator<=(unsigned int const& val)
{
	if (d <= val)
		return true;
	else
		return false;
}

bool day::operator==(unsigned int const& val)
{
	if (d == val)
		return true;
	else
		return false;
}

bool day::operator!=(unsigned int const& val)
{
	if (d != val)
		return true;
	else
		return false;
}
