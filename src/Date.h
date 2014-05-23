#pragma once

#include "Includer.h"



class Date
{
private:
	WeekDay day;
	int hour, min;
public:
	Date(void);
	Date(WeekDay, int hour, int min);
	~Date(void);
	string PrintDate();
	int turnToMinutes();
	bool operator<(Date d)
	{
		return (int)day * 24*60*60  + hour*60 + min < (int)d.day * 24*60*60  + d.hour*60 + d.min ;
	}
	WeekDay getDay() const;


};

