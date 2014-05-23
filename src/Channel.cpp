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
	sort(programs.begin(), programs.end());
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

bool Channel:: CheckIfValidTimeForNewProgram(Program* p)
{
	for( unsigned int i = 0 ; i < programs.size(); i ++)
	{
		if (i = programs.size()-1){
			if ( programs[i]->getDate() < p->getDate())
				return true;
			else
				return false;
		}
		else{
		if ( programs[i]->getDate() < p->getDate())
			if(p->getDate().turnToMinutes() + p->getDuration() < programs[i+1]->getDate().turnToMinutes())
				return true;
			else
				return false;
		}
	}
	
}