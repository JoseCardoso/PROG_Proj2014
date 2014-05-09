#pragma once

using namespace std;

enum WeekDay {
	SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY 
};

class Date
{
private:
	WeekDay day;
	int hour, min;
public:
	Date(void);
	Date(WeekDay, int hour, int min);
	~Date(void);
	bool operator<(Date d)
	{
		return (int)day * 24*60*60  + hour*60 + min < (int)d.day * 24*60*60  + d.hour*60 + d.min ;
	}

};

