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
		for ( unsigned int j = 0 ; j < channels.getPrograms() ; j ++)
		{
			if ( channels.get


		}
	}


}
vector<Program*> Box::listByChannel(string  channel, string day) const{
}
vector<Program*> Box::listByType(string  type, string day) const{
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
