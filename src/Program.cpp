#include "Program.h"


Program::Program(void)
{
}


Program::~Program(void)
{
}


WeekDay Program::getWeekDay()
{
	return exhibitionDate.getDay();
}

ProgramType Program:: getProgramType()
{
	return type;
}