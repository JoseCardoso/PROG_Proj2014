#include "Channel.h"


Channel::Channel(void)
{
}


Channel::~Channel(void)
{
}


Channel::Channel(string name)
{
	this->name= name;
}

vector <Program*> Channel:: getPrograms() const
{

	return programs;
}

string Channel:: getName() const
{
	return name;
}


void Channel:: addProgram(Program* program)
{
	programs.push_back(program);
}

void Channel:: removeProgram(string programName)
{
	vector <Program*> temp;

	for (unsigned int i = 0 ; i < programs.size() ; i++)
	{
		if (convertToLowerCase(programName) != convertToLowerCase(programs[i]->getName()))
			temp.push_back(programs[i]);
	}

	programs.clear();

	programs = temp;
}