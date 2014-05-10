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
			if ( channels[i]->getPrograms()[j]->getDate().getDay() == day)
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;

}

vector<Program*> Box::listByChannel(string  channel, WeekDay day) const{


	vector<Program*>res;

	for (unsigned int i = 0 ; i < channels.size(); i++)
	{
		for ( unsigned int j = 0 ; j < channels[i]->getPrograms().size() ; j ++)
		{
			if ( channels[i]->getPrograms()[j]->getDate().getDay() == day  && convertToLowerCase(channels[i]->getName()) == convertToLowerCase(channel) )
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;
}

vector<Program*> Box::listByType(ProgramType type, WeekDay day) const{

	vector<Program*>res;

	for (unsigned int i = 0 ; i < channels.size(); i++)
	{
		for ( unsigned int j = 0 ; j < channels[i]->getPrograms().size() ; j ++)
		{
			if ( channels[i]->getPrograms()[j]->getDate().getDay() == day  && channels[i]->getPrograms()[j]->getProgramType() == type )
			{
				res.push_back(channels[i]->getPrograms[j]);
			}

		}
	}

	return res;

}

bool Box::rentMovies(string title){

	bool found = false;

	vector <Movie *> temp;

	for ( unsigned int i = 0 ; i < movies.size() ; i ++ )
	{
		if (!found)
		{
			if ( convertToLowerCase(movies[i]->getName()) == convertToLowerCase(title))
			{
				movies[i]->incRented();
				found = true;
			}
		}
		temp.push_back(movies[i]);

	}

	for ( unsigned int i = 0 ; i < viewedMovies.size() ; i ++ )
	{
		if ( !found)
		{
			if ( convertToLowerCase(viewedMovies[i]->getName()) == convertToLowerCase(title))
			{
				viewedMovies[i]->incRented();
			}

		}
		temp.push_back(viewedMovies[i]);
	}

	movies.clear();
	viewedMovies.clear();



	for ( unsigned int i = 0 ; i < temp.size() ; i ++)
	{
		if (temp[i]->getRentedTimes > 0)
			viewedMovies.push_back(temp[i]);
		else
			movies.push_back(temp[i]);
	}
}

float Box::moneySpent() const
{
	float res;

	for (unsigned int i = 0 ; i < viewedMovies.size() ; i++)
	{
		res += (float) viewedMovies[i]->getCost() * viewedMovies[i]->getRentedTimes();
	}

	return res;
}

int Box::timesWhatched(string title) const{

	for (unsigned int i = 0 ; i < viewedMovies.size() ; i++)
	{
		if (convertToLowerCase(title) == convertToLowerCase(viewedMovies[i]->getName()))
			return viewedMovies[i]->getRentedTimes();
	}
	
	return 0;

}

bool Box::changePassword()// ask, verify and change the password
{
	string input, previousPass = ownerPass;
	cout <<"Please input previous password: ";

	cin.ignore();
	getline(cin, input);

	if (input == ownerPass)
	{
		do 
		{
			
		cout << "\nPlease enter new password: ";
	
		cin.ignore();
		getline(cin,input);
		ownerPass = input;

		} while (input == previousPass);

		cout << "\nPassword changed";
		return true;
	}
	else
		return false;




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
