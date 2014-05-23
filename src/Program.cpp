#include "Program.h"


Program::Program(void)
{
}


Program::~Program(void)
{
}


Program::Program(string name, ProgramType type, int duration, Date exhibitionDate)
{

	this->name=name;
	this->type = type;
	this->duration = duration;
	this->exhibitionDate = exhibitionDate;

}


string Program::getBelongsToChannel() const{
	return belongsToTheChannel;
}
void Program::setBelongsToChannel(string belongsToTheChannel){
	this->belongsToTheChannel = belongsToTheChannel;
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

bool Program::getRecorded() const
{
	return recorded;
}

void Program::setRecorded(bool recorded)
{
	recorded = this->recorded;
}

bool Program:: getToBeRecorded() const{
	return toBeRecorded;
}

void Program:: setToBeRecorded(bool toBeRecorded)
{
	this->toBeRecorded = toBeRecorded;

}