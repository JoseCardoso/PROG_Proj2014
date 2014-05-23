#include "Box.h"


Box::Box(void)
{

	viewedMovies.clear();
	recordList.clear();
	movies.clear();
	channels.clear();
	adminLogin=false;
}


Box::~Box(void)
{

}

Box::Box(string passwd, Date Date)
{
	viewedMovies.clear();
	recordList.clear();
	movies.clear();
	channels.clear();
	ownerPass=passwd;
	this->currentDate=currentDate;
	adminLogin = false;

}

bool Box::getAdminLogin() const{

	return adminLogin;
}

void Box::setAdminLogin(bool login){

	adminLogin = login;
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
				res.push_back(channels[i]->getPrograms()[j]);
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
				res.push_back(channels[i]->getPrograms()[j]);
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
				res.push_back(channels[i]->getPrograms()[j]);
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
		if (temp[i]->getRentedTimes() > 0)
			viewedMovies.push_back(temp[i]);
		else
			movies.push_back(temp[i]);
	}

	return found;
}

float Box::moneySpent() const
{
	float res = 0;

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

string Box::getPassword() const
{
	return ownerPass;
}

// Channel CRUD
bool Box::createdChanel()
{

	string name = "";
	do{
		ClearScr();
		cout << "Enter The Name Of The Channel: ";
		name = inputString();

	} while (name == "");

	Channel* c1 = new Channel(name);

	channels.push_back(c1);

	return true;
}

bool Box::removeChanel(int i)
{
	channels.erase(channels.begin() + i);

	return true;
}

bool Box::updateChanel(char op, int i) // i representa o id do canal no vector de canais
{
	ClearScr();

	switch (op)
	{
	case '1': //Change Name
		cout << "Enter Name: (must be a new unused name): ";
		if(checkNewChannelName(inputString()))
			channels[i]->
			break;
	case '2'://AddNewProgram
		break;
	case '3': //Remove a program
		break;

	}

}

// Program CRUD
bool Box::createdProgram(int i)
{
	string name = "";
	int duration = 0, hour =0 , minute = 0;
	string day , type; 
	do{
		ClearScr();
		cout << "Enter The Name Of The Program: ";
		name = inputString();
		cout << "\nEnter The Type Of The Program: ";
		type = inputString();
		cout << "\nEnter The WeekDay Of The Program: ";
		day = inputString();
		cout << "\nEnter The Hour Of Exhibition: ";
		hour = Value();
		cout << "\nEnter The Minutes Of Exhibition: ";
		minute = Value();
		cout << "\nEnter The Duration Of The Program: ";
		duration = Value();

	} while (name == "" && duration == 0 && !checkValidWeekDay(day) && !checkValidProgramType(type));


	Program* p = new Program(name,convertStringToProgramType(type),duration, Date(convertStringToWeekDay(day), hour, minute));

	if(channels[i]->CheckIfValidTimeForNewProgram(p))
	{
		p->setBelongsToChannel(channels[i]->getName());
		channels[i]->addProgram(p);
	}


}

bool Box::removeProgram(int i)
{
	string programName = recordList[i]->getName();

	for (unsigned int j = 0 ; j < channels.size() ; j++)
	{
		channels[j]->removeProgram(programName);
	}

	recordList.erase(recordList.begin() + i);

}

bool Box::updateProgram(char op, int i)
{
}

// Movie CRUD
bool Box::createdMovie()
{

	string name = "";
	int cost = 0, hour =0 , minute = 0;
	string day , type; 
	do{
		ClearScr();
		cout << "Enter The Name Of The Movie: ";
		name = inputString();
		cout << "Enter The Hour Of Exhibition: ";
		cost = Value();
		cout << "Enter Cost: ";
		minute = Value();
	} while (name == "" && cost == 0);


}

bool Box::removeMovie(int i)
{
	movies.erase(movies.begin() + i);
}

bool Box::updateMovie(char op , int i)
{
}

void Box::PrintProgramsByDay(int i , WeekDay day){ 

	ClearScr(); 
	vector <Program *> programsOnThatDay = listByDay(day);


	cout << "                         -------- Programs --------" << endl;
	cout << "\nName: " << programsOnThatDay[i]->getName() <<"\nChannel: " << programsOnThatDay[i]->getBelongsToChannel() << "\nDuration: "<< programsOnThatDay[i]->getDuration() <<"\nProgram Type: " << convertProgramTypeToString(programsOnThatDay[i]->getProgramType()) <<"\nDate: " << programsOnThatDay[i]->getDate().PrintDate();
	cout << "\nRecord: ";
	if (programsOnThatDay[i]->getRecorded())
		cout << "YES";
	else
	{
		cout << "NO";
		cout <<"\nTo Be Recorded: ";
		if (recordList[i]->getToBeRecorded())
			cout << "YES"; else cout << "NO";
	}
	cout << "\n\nUse The Arrows To Move Across The Programs List\n\n1- Set To Be Recorded\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

} 

void Box::PrintProgramsByChannel(int i ,string channel ,WeekDay day){ 

	ClearScr(); 
	vector <Program *> programsOnThatDay = listByChannel(channel,day);

	cout << "                         -------- Programs --------" << endl;
	cout << "\nName: " << programsOnThatDay[i]->getName() <<"\nChannel: " << programsOnThatDay[i]->getBelongsToChannel() <<"\nDuration: "<< programsOnThatDay[i]->getDuration() <<"\nProgram Type: " << convertProgramTypeToString(programsOnThatDay[i]->getProgramType()) <<"\nDate: " << programsOnThatDay[i]->getDate().PrintDate();
	cout << "\nRecord: ";
	if (programsOnThatDay[i]->getRecorded())
		cout << "YES"; 
	else
	{
		cout << "NO";
		cout <<"\nTo Be Recorded: ";
		if (recordList[i]->getToBeRecorded())
			cout << "YES"; else cout << "NO";
	}
	cout << "\n\nUse The Arrows To Move Across The Programs List\n\n1- Buy\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

} 

void Box::PrintProgramsByType(int i , ProgramType type, WeekDay day){ 

	ClearScr();
	vector <Program *> programsOnThatDay = listByType(type, day);

	cout << "                         -------- Programs --------" << endl;
	cout << "\nName: " << programsOnThatDay[i]->getName() <<"\nChannel: " << programsOnThatDay[i]->getBelongsToChannel() <<"\nDuration: "<< programsOnThatDay[i]->getDuration() <<"\nProgram Type: " << convertProgramTypeToString(programsOnThatDay[i]->getProgramType()) <<"\nDate: " << programsOnThatDay[i]->getDate().PrintDate();
	cout << "\nRecord: ";
	if (programsOnThatDay[i]->getRecorded())
		cout << "YES"; 
	else
	{
		cout << "NO";
		cout <<"\nTo Be Recorded: ";
		if (recordList[i]->getToBeRecorded())
			cout << "YES"; else cout << "NO";
	}
	cout << "\nUse The Arrows To Move Across The Programs List\n\n1- Set To Be Recorded\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

} 

void Box::PrintMovies(int i){

	vector <Movie* > allMovies = movies;

	for (unsigned int j = 0 ; j < viewedMovies.size() ; j++)
	{
		allMovies.push_back(viewedMovies[j]);

	}

	ClearScr();


	cout << "                         -------- Movies --------" << endl;
	cout << "\nName: " << allMovies[i]->getName() <<"\nCost: "<< allMovies[i]->getCost();
	if (allMovies[i]->getRentedTimes() == 0)
		cout << "Unseen"; else { cout << "Times watched: " << allMovies[i]->getRentedTimes() << endl;}

	if (!adminLogin)
		cout << "\n\nUse The Arrows To Move Across The Movie Listt\n\n1- Rent\n0- Quit" << endl; 
	else
		cout << "\n\nUse the arrows to move across the Piece List\n\n1- Rent\2-Change Movie Name\n3-Change Movie Cost\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

} 

void Box::PrintAllPrograms(int i){

	ClearScr(); 

	cout << "                         -------- Programs --------" << endl;
	cout << "\nName: " << recordList[i]->getName() <<"\nChannel: " << recordList[i]->getBelongsToChannel() <<"\nDuration: "<< recordList[i]->getDuration() <<"\nProgram Type: " << convertProgramTypeToString(recordList[i]->getProgramType()) <<"\nDate: " << recordList[i]->getDate().PrintDate();
	cout << "\nRecord: ";
	if (recordList[i]->getRecorded())
		cout << "YES"; 
	else
	{
		cout << "NO";
		cout <<"\n To Be Recorded: ";
		if (recordList[i]->getToBeRecorded())
			cout << "YES"; else cout << "NO";
	}
	cout << "\n\nUse The Arrows To Move Across The Programs List\n\n1- Change Name\n2- Change Duration\n3- Change Program Type\n4- Change Day Of The Week\n5- Change Airing Time\n6- Delete Program\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

}

void Box::PrintAllChannels(int i)
{
	ClearScr(); 

	cout << "                         -------- Channels --------" << endl;
	cout << "\nName: " << channels[i]->getName() <<"\nNumber Of Programs: " << channels[i]->getPrograms().size()<< "\n\n";
	for (unsigned int j = 0 ; j < channels[i]->getPrograms().size(); j++)
	{
		cout << j+1 << channels[i]->getPrograms()[j]->getName() << endl;
	}
	cout << "\n\nUse The Arrows To Move Across The Channel List\n\n1- Change Name\n2- Add New Program\n3- Remove A Program\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

}

bool Box::checkNewChannelName(string name)
{
	for (int i = 0 ; i< channels.size() ; i++)
	{
		if (channels[i]->getName() == name)
			return false;
	}

	return true;

}