#include "Channel.h"


Channel::Channel(void)
{
}


Channel::~Channel(void)
{
}

vector <Program*> Channel:: getPrograms(){

	return programs;
}

string Channel:: getName()
{
	return name;
}
