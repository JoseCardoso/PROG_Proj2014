#pragma once

#include <string>
#include <vector>

#include "Date.h"

enum ProgramType {
	NEW, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING
};

using namespace std;

class Program
{
private:
	string name;
	ProgramType type;
	bool recorded;
	int duration;
	Date exhibitionDate;
public:
	Program(void);
	~Program(void);
	WeekDay getWeekDay();
	ProgramType getProgramType();
};

