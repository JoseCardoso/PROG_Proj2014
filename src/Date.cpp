#include "Date.h"


Date::Date(void)
{
}

Date::Date(WeekDay day, int hour, int min)
{
	this->day = day;
	this->hour= hour;
	this->min = min;
}


Date::~Date(void)
{
}


WeekDay Date::getDay() const
{
	return day;
}

string Date::PrintDate()
{
	string output = convertWeekDayToString(day) + " " + convertIntToString(hour) + "h" + convertIntToString(min) +"m";

	return output;
}

int Date::turnToMinutes()
{
	return (int)day * 24*60*60  + hour*60 + min;
}

int Date::getMinutes()
{
	return min;
}

int Date::getHour()
{
	return hour;
}