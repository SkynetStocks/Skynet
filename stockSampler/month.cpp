#include "month.h"


//logic operators
bool month::operator>(month const& val)
{
	if (m > val.getMonth())
		return true;
	else
		return false;
}

bool month::operator<(month const& val)
{
	if (m < val.getMonth())
		return true;
	else
		return false;
}

bool month::operator>=(month const& val)
{
	if (m >= val.getMonth())
		return true;
	else
		return false;
}

bool month::operator<=(month const& val)
{
	if (m <= val.getMonth())
		return true;
	else
		return false;
}

bool month::operator==(month const& val)
{
	if (m == val.getMonth())
		return true;
	else
		return false;
}

bool month::operator!=(month const& val)
{
	if (m != val.getMonth())
		return true;
	else
		return false;
}


bool month::operator>(unsigned int const& val)
{
	if (m > val)
		return true;
	else
		return false;
}

bool month::operator<(unsigned int const& val)
{
	if (m < val)
		return true;
	else
		return false;
}

bool month::operator>=(unsigned int const& val)
{
	if (m >= val)
		return true;
	else
		return false;
}

bool month::operator<=(unsigned int const& val)
{
	if (m <= val)
		return true;
	else
		return false;
}

bool month::operator==(unsigned int const& val)
{
	if (m == val)
		return true;
	else
		return false;
}

bool month::operator!=(unsigned int const& val)
{
	if (m != val)
		return true;
	else
		return false;
}
