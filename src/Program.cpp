#include "Program.h"


Program::Program(void)
{
}


Program::~Program(void)
{
}


Date Program::getDate() const
{
	return exhibitionDate;
}

ProgramType Program:: getProgramType() const
{
	return type;
}

int Program:: getDuration() const
{
	return duration;
}

string Program:: getName() const
{
	return name;
}


 void Program::setRecorded(bool recorded)
{
	recorded = this->recorded;
}