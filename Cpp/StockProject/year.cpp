#include "year.h"

//logic operators
bool year::operator>(year const& val)
{
	if (y > val.getYear())
		return true;
	else
		return false;
}

bool year::operator<(year const& val)
{
	if (y < val.getYear())
		return true;
	else
		return false;
}

bool year::operator>=(year const& val)
{
	if (y >= val.getYear())
		return true;
	else
		return false;
}

bool year::operator<=(year const& val)
{
	if (y <= val.getYear())
		return true;
	else
		return false;
}

bool year::operator==(year const& val)
{
	if (y == val.getYear())
		return true;
	else
		return false;
}

bool year::operator!=(year const& val)
{
	if (y != val.getYear())
		return true;
	else
		return false;
}


bool year::operator>(unsigned int const& val)
{
	if (y > val)
		return true;
	else
		return false;
}

bool year::operator<(unsigned int const& val)
{
	if (y < val)
		return true;
	else
		return false;
}

bool year::operator>=(unsigned int const& val)
{
	if (y >= val)
		return true;
	else
		return false;
}

bool year::operator<=(unsigned int const& val)
{
	if (y <= val)
		return true;
	else
		return false;
}

bool year::operator==(unsigned int const& val)
{
	if (y == val)
		return true;
	else
		return false;
}

bool year::operator!=(unsigned int const& val)
{
	if (y != val)
		return true;
	else
		return false;
}