#include "Box.h"


Box::Box(void)
{

	viewedMovies.clear();
	recordList.clear();
	movies.clear();
	channels.clear();
}


Box::~Box(void)
{

}



Box::Box(string passwd, Date currentDate)
{
	ownerPass=passwd;
	currentDate=this->currentDate;

}

vector<Program*> Box::listByDay(WeekDay day) const
{
	vector<Program*>res;

	for (unsigned int i = 0 ; i < channels.size(); i++)
	{
		for ( unsigned int j = 0 ; j < channels[i]->getPrograms().size() ; j ++)
		{
			if ( channels[i]->getPrograms()[j]->getWeekDay() == day)
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;

}
vector<Program*> Box::listByChannel(string  channel, string day) const{


	vector<Program*>res;

	for (unsigned int i = 0 ; i < channels.size(); i++)
	{
		for ( unsigned int j = 0 ; j < channels[i]->getPrograms().size() ; j ++)
		{
			if ( channels[i]->getPrograms()[j]->getWeekDay() == day  && channels[i]->getName() == channel )
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;
}
vector<Program*> Box::listByType(ProgramType type, string day) const{

	vector<Program*>res;

	for (unsigned int i = 0 ; i < channels.size(); i++)
	{
		for ( unsigned int j = 0 ; j < channels[i]->getPrograms().size() ; j ++)
		{
			if ( channels[i]->getPrograms()[j]->getWeekDay() == day  && channels[i]->getName() == channel channels[i]->getPrograms()[j]->getProgramType() == type )
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;

}
bool Box::rentMovies(string title){
}
float Box::moneySpent() const
{
}
int Box::timesWhatched(string title) const{
}
bool Box::changePassword()// ask, verify and change the password
{
}
// Channel CRUD
bool Box::createdChanel()
{
}
bool Box::removeChanel()
{
}
bool Box::updateChanel()
{
}
// Program CRUD
bool Box::createdProgram(string chanel)
{
}
bool Box::removeProgram()
{
}
bool Box::updateProgram()
{
}
// Movie CRUD
bool Box::createdMovie()
{
}
bool Box::removeMovie()
{
}
bool Box::updateMovie()
{
}
