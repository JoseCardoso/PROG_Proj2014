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
	this->currentDate=Date;
	adminLogin = false;

}

bool Box::getAdminLogin() const{

	return adminLogin;
}

void Box::setAdminLogin(bool login){

	adminLogin = login;
}

Date Box::getCurrentDate()
{
	return currentDate;
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
	ClearScr();
	string input, previousPass = ownerPass;
	cout <<"Please input previous password: ";


	getline(cin, input);

	if (input == ownerPass)
	{
		do 
		{

			cout << "\nPlease enter new password: ";

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
void Box::createdChanel()
{

	string name = "";
	do{
		ClearScr();
		cout << "Enter The Name Of The Channel: ";
		name = inputString();

	} while (name == "");

	Channel* c1 = new Channel(name);

	channels.push_back(c1);


}

void Box::removeChanel(int i)
{
	for (unsigned int j = 0 ; j< channels[i]->getPrograms().size() ; j++)
	{
		channels[i]->getPrograms()[j]->setBelongsToChannel("NONE");
	}

	channels.erase(channels.begin() + i);

}

void Box::updateChanel(char op, int i) // i representa o id do canal no vector de canais
{
	ClearScr();
	string name;

	switch (op)
	{
	case '1': //Change Name
		cout << "Enter Name: (must be a new unused name): ";
		name = inputString();
		if(checkNewChannelName(name))
			channels[i]->setName(name);
		break;
	case '2':
		createdProgram(i);
		break;
	case '3'://Remove a Program
		int choice=0;
		do {
			ClearScr();
			
			cout << "Choose ID of the program you want to remove: \n\n";
			for (unsigned int j = 0 ; j < channels[i]->getPrograms().size();j++)
			{
				cout << j+1 <<"- " << channels[i]->getPrograms()[j]->getName() << endl;
			}
			choice = Value();
		}while( choice < 1 && choice > channels[i]->getPrograms().size() + 1);

		if ( choice < 1 && choice > channels[i]->getPrograms().size() + 1)
			cout << "\nCan't remove that program";
		else{
			string name = channels[i]->getPrograms()[choice-1]->getName();
			channels[i]->getPrograms()[choice-1]->setBelongsToChannel("NONE");
			channels[i]->removeProgram(name);

		}
	}

}

// Program CRUD
void Box::createdProgram(int i)
{
	string name = "";
	int duration = 0, hour =0 , minute = 0;
	string day , type; 
	do{
		ClearScr();
		cout << "Enter The Name Of The Program: ";
		name = inputString();
		cout << "\nEnter The Type Of The Program: ";
		type = convertToUpperCase(inputString());
		cout << "\nEnter The WeekDay Of The Program: ";
		day = convertToUpperCase(inputString());
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
	else 
	{
		cout << "\nThere was a program in this schedule. Programs Overlaped." <<endl;
		Sleep(2000);
	}

	if (p->getDate() < currentDate)
	{
		p->setRecorded(true);
		p->setToBeRecorded(true);
	}
	else
	{
		p->setRecorded(false);
		p->setToBeRecorded(false);
	}


}

void Box::removeProgram(int i)
{
	string programName = recordList[i]->getName();

	for (unsigned int j = 0 ; j < channels.size() ; j++)
	{
		channels[j]->removeProgram(programName);
	}

	recordList.erase(recordList.begin() + i);

}

void Box::updateProgram(char op, int i)
{
	ClearScr();
	string name="";
	int time;

	switch (op)
	{
	case '1': //Change Name
		cout << "Enter Name: (must be a new unused name): ";
		name = inputString();
		if(checkNewProgramName(name))
			recordList[i]->setName(name);
		break;
	case '2'://Change duration
		cout << "Enter new duration: ";
		time = Value();

		for (unsigned int k = 0 ; k < channels.size() ; k++){

			if (channels[k]->getName() == recordList[i]->getBelongsToChannel())
			{
				for (unsigned int j = 0 ;  j < channels[i]->getPrograms().size() ; j++)
				{
					if ( j < channels[k]->getPrograms().size() -1)
						if (channels[k]->getPrograms()[j]->getName() == recordList[i]->getName())
						{
							if (channels[k]->getPrograms()[j+1]->getDate().turnToMinutes() > recordList[i]->getDate().turnToMinutes() + time)
								recordList[i]->setDuration(time);
						} 
				}
			}

		}
		break;

	case '3'://Change Program Type
		cout<< "Please enter the new Type (NEWS, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING):" ;
		name = convertToUpperCase(inputString());
		if (checkValidProgramType(name))
			recordList[i]->setProgramType(convertStringToProgramType(name));
		else
		{
			cout <<"\nNot a valid type;";
			Sleep(800);
		}
		break;
	case '4'://Delete Program
		removeProgram(i);
		break;
	}
}

// Movie CRUD
void Box::createdMovie()
{

	string name = "";
	int cost = 0; 
	do{
		ClearScr();
		cout << "Enter The Name Of The Movie: ";
		name = inputString();
		cout << "Enter Cost: ";
		cost = Value();
	} while (name == "" && cost == 0);

	Movie* m = new Movie(name , cost);
	movies.push_back (m);


}

void Box::removeMovie(int i)
{
	movies.erase(movies.begin() + i);
}

void Box::updateMovie(char op , int i)
{

	ClearScr();
	string name="";
	int cost;
	vector <Movie * > temp;

	for (unsigned int j = 0 ; j < movies.size() ; j++)
	{
		temp.push_back(movies[j]);
	}
	for (unsigned int j = 0 ; j < viewedMovies.size() ; j++)
	{
		temp.push_back(viewedMovies[j]);
	}

	switch (op)
	{
	case '2': //Change Name
		cout << "Enter Name: (must be a new unused name): ";
		name = inputString();
		if(!checkNewMovieName(name))
			temp[i]->setName(name);
		break;
	case '3':
		cout << "Enter Cost: ";
		cost = Value();
		temp[i]->setCost(cost);
		break;
	}

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
	cout << "\n\nUse The Arrows To Move Across The Programs List\n\n1- Set To Be Recorded\n\n0- Quit" << endl; 
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
		cout << "\nUnseen"; else { cout << "\nTimes watched: " << allMovies[i]->getRentedTimes() << endl;}

	if (!adminLogin)
		cout << "\n\nUse The Arrows To Move Across The Movie List\n\n1- Rent\n0- Quit" << endl; 
	else
		cout << "\n\nUse the Arrows To Move Across The Movie List\n\n1- Rent\n2- Change Movie Name\n3- Change Movie Cost\n4- Create New Movie\n5- Remove Movie\n0- Quit" << endl; 
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
	cout << "\n\nUse The Arrows To Move Across The Programs List\n\n1- Change Name\n2- Change Duration\n3- Change Program Type\n4- Delete Program\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

}

void Box::PrintAllChannels(int i)
{
	ClearScr(); 

	cout << "                         -------- Channels --------" << endl;
	cout << "\nName: " << channels[i]->getName() <<"\nNumber Of Programs: " << channels[i]->getPrograms().size()<< "\n\n";
	for (unsigned int j = 0 ; j < channels[i]->getPrograms().size(); j++)
	{
		cout << j+1 <<"- " << channels[i]->getPrograms()[j]->getName() << endl;
	}
	cout << "\n\nUse The Arrows To Move Across The Channel List\n\n1- Change Name\n2- Add New Program\n3- Remove A Program\n4- Create New Channel\n5- Remove Channel\n\n0- Quit" << endl; 
	cout << " " << string(78, '-') << endl; 

}

bool Box::checkNewChannelName(string name)
{
	for (unsigned int i = 0 ; i< channels.size() ; i++)
	{
		if (channels[i]->getName() == name)
			return false;
	}

	return true;

}

bool Box::checkNewProgramName(string name)
{
	for (unsigned int i = 0 ; i< recordList.size() ; i++)
	{
		if (recordList[i]->getName() == name)
			return false;
	}

	return true;

}

bool Box::checkNewMovieName(string name)
{
	bool found = false;


	for (unsigned int i = 0 ; i< movies.size() ; i++)
	{
		if (movies[i]->getName() == name)
		{
			found = true;
			break;
		}
	}

	if (!found)
		for (unsigned int i = 0 ; i< viewedMovies.size() ; i++)
		{
			if (viewedMovies[i]->getName() == name)
			{
				found = true;
				break;
			}
		}


		return found;

}

vector<Movie* > Box::getMovies()
{
	return movies;
}

vector<Movie*> Box::getViewedMovies(){
	return viewedMovies;
}

vector<Program*> Box::getRecordList(){
	return recordList;
}

vector<Channel*> Box::getChannels(){
	return channels;
}

vector <Movie *> Box:: getAllMovies()
{
	vector<Movie*> temp;

	for (unsigned int i = 0 ; i < movies.size() ; i ++)
	{
		temp.push_back(movies[i]);
	}
	for (unsigned int i = 0 ; i < viewedMovies.size(); i++)
	{
		temp.push_back(viewedMovies[i]);
	}

	return temp;
}

void Box:: saveGeneralInfo() {
	ofstream outputFile; 
	outputFile.open("generalInfo.txt"); 
	if (outputFile.fail()) 
	{ 
		outputFile.clear(); 
	} 
	else
	{
		//Password - number of channels- nMovies  - nViewedMovies - nPrograms

		outputFile << ownerPass << " " << channels.size() << " " <<  movies.size() << " " << viewedMovies.size() << " " << recordList.size();

	} 

	outputFile.close(); 
}
void Box:: loadGeneralInfo()
{
	string password;
	int nChanels, nMovies, nViewedMovies, nPrograms;

	ifstream fin;
	fin.open("generalInfo.txt");
	if (!fin) {
		return;
	}

	fin >> password >> nChanels >> nMovies >> nViewedMovies >> nPrograms;

	ownerPass = password;

}

void Box:: saveChannels() {
	ofstream outputFile; 
	outputFile.open("ChannelsList.txt"); 
	if (outputFile.fail()) 
	{ 
		outputFile.clear(); 
	} 
	else
	{
		outputFile << channels.size(); 
		//Password - number of channels- nMovies  - nViewedMovies - nPrograms

		for (unsigned int i = 0 ; i < channels.size(); i++){


			outputFile << endl <<channels[i]->getName();
		}
	} 

	outputFile.close(); 
}

void Box:: savePrograms() {
	ofstream outputFile; 
	outputFile.open("ProgramsList.txt"); 
	if (outputFile.fail()) 
	{ 
		outputFile.clear(); 
	} 
	else
	{
		outputFile << recordList.size(); 

		for (unsigned int i = 0 ; i < recordList.size(); i++){

			outputFile << endl <<recordList[i]->getName() << " " << convertProgramTypeToString(recordList[i]->getProgramType()) << " " << recordList[i]->getBelongsToChannel() << " " << recordList[i]->getRecorded() << " " << recordList[i]->getToBeRecorded() << " " << recordList[i]->getDuration() << " " <<convertWeekDayToString(recordList[i]->getDate().getDay()) << " " << recordList[i]->getDate().getHour() << " " << recordList[i]->getDate().getMinutes();
		}
	} 

	outputFile.close(); 
}

void Box:: saveMovies() {
	ofstream outputFile; 
	outputFile.open("MovieList.txt"); 
	if (outputFile.fail()) 
	{ 
		outputFile.clear(); 
	} 
	else
	{
		outputFile << movies.size() + viewedMovies.size(); 

		for (unsigned int i = 0 ; i < movies.size(); i++){

			outputFile << endl <<movies[i]->getName() << " " << movies[i]->getCost() << " " << movies[i]->getRentedTimes();
		} 

		for (unsigned int i = 0 ; i < viewedMovies.size(); i++){

			outputFile << endl <<viewedMovies[i]->getName() << " " << viewedMovies[i]->getCost() << " " << viewedMovies[i]->getRentedTimes();
		} 
		outputFile.close(); 
	}
}

void Box::loadChannels()
{
	ifstream fin;
	fin.open("ChannelsList.txt");
	if (!fin)
		cout << "ERROR";

	int n;
	fin >> n;


	for (int i = 0; i < n; i++) {
		string temp;
		fin >> temp;

		Channel* c = new Channel(temp);
		channels.push_back(c);
	}


}

void Box::loadPrograms()
{
	ifstream fin;
	fin.open("ProgramsList.txt");
	if (!fin)
		cout << "ERROR";

	string nome, tipo , canal , weekday;
	bool recorded, toberecord;
	int duration, hour , minutes;

	int n;
	fin >> n;


	for (int i = 0; i < n; i++) {

		fin >> nome >> tipo >> canal >> recorded >> toberecord >> duration >> weekday >> hour >> minutes;

		Program* p = new Program(nome, convertStringToProgramType(convertToUpperCase(tipo)), duration, Date(convertStringToWeekDay(convertToUpperCase(weekday)),hour, minutes));


		if (p->getDate() < currentDate){
			p->setRecorded(true);
			p->setToBeRecorded(true);
		}
		else
		{			
			p->setRecorded(false);
			if (toberecord)
				p->setToBeRecorded(true);
			else
				p->setToBeRecorded(false);
		}

		p->setBelongsToChannel(canal);
		recordList.push_back(p);

		for (unsigned int i = 0 ; i < channels.size() ; i++)
		{
			if (canal == channels[i]->getName())
			{
				channels[i]->addProgram(p);
			}
		}
	}
}

void Box::loadMovies()
{
	ifstream fin;
	fin.open("MovieList.txt");
	if (!fin)
		cout << "ERROR";

	string nome;
	int cost, rentedTimes;

	int n;
	fin >> n;

	for (int i = 0; i < n; i++) {

		fin >> nome >> cost >> rentedTimes;
		Movie * m = new Movie(nome, cost);
		m->setRentedTimes(rentedTimes);
		if(rentedTimes >0)
			viewedMovies.push_back(m);
		else
			movies.push_back(m);
	}

}