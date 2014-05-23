#include "Includer.h"
#include "Box.h"

using namespace std;



// Randomly generates a valid day, hour and minute
Date currentDate(){

	int day = rand() % 7;
	int hour = rand() % 24;
	int min = rand() % 60;

	switch(day)
	{
	case 0:
		return Date(SUNDAY, hour , min);
		break;
	case 1:
		return Date(MONDAY, hour , min);
		break;
	case 2:
		return Date(TUESDAY, hour , min);
		break;
	case 3:
		return Date(WEDNESDAY, hour , min);
		break;
	case 4:
		return Date(THURSDAY, hour , min);
		break;
	case 5:
		return Date(FRIDAY, hour , min);
		break;
	case 6:
		return Date(SATURDAY, hour , min);
		break;
	}


}

using namespace std;

int main(){

	srand(time(NULL));
	//need to load from file, for now password will be 1234
	Box box = Box("1234", currentDate());

	hideCursor();

	bool login = false;


	unsigned char op;

	do {
		ClearScr();
		if (!box.getAdminLogin())
			cout << "                            TV BOX\n\nMenu:\n\n1- Login As Admin\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n6- Movie Club\n\n0- Exit";
		else
			cout << "                            TV BOX\n\nMenu:\n\n1- Login As Admin\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n6- Movie Club\n7- Manage Programs\n8- Manage Channels\n\n0- Exit";

		op = _getch();
		switch (op) {
		case '0'://Exit
			{
				return 0;
			}
		case '1'://Login as admin
			{
				string password;

				if (!login)
				{		cin.clear();
				ClearScr();
				cout << "Enter Password: ";
				password = inputString();

				if (password == box.getPassword()){
					login = true;
					box.setAdminLogin(true);
				}
				if (!login)
				{
					cout << "\nThat Password is wrong. Please try again.";
					Sleep(1000);
				}
				}
				else
				{
					cout << "\n\nYou are already logged in.";
					Sleep(1000);
				}
				break;
			}
		case '2': // Listagem de programas por dia
			{
				unsigned int i = 0; 

				string weekDay = "";

				cin.clear();
				ClearScr();

				cout << "Enter Weekday: ";
				weekDay = convertToUpperCase(inputString());

				if (weekDay != "")
				{


					if(box.listByDay(convertStringToWeekDay(weekDay)).empty()) 
					{ 
						cout << "\nThere is no programs that day"; 
						Sleep(1000); 
						break; 
					} 
					else
					{ 
						box.PrintProgramsByDay(i ,convertStringToWeekDay(weekDay)); 
						do
						{ 
							unsigned char a = _getch(); 
							if(a == 77) 
							{ 
								i++; 
							} 
							else if(a == 75) 
							{ 
								i=i-1; 
							} 

							else if(a == '1') 
							{ 
								break; 
							} 

							if(i < 0) 
							{ 
								i = box.listByDay(convertStringToWeekDay(weekDay)).size()-1; 
							} 
							if(i > box.listByDay(convertStringToWeekDay(weekDay)).size()-1) 
							{ 
								i = 0; 
							} 

							box.PrintProgramsByDay(i ,convertStringToWeekDay(weekDay)); 

						}while(true); 
						break; 
					}
				}

			}
		case '3': // Listagem de programas por Canal
			{
				unsigned int i = 0; 
				string channelName="";
				string weekDay="";

				cin.clear();
				ClearScr();
				cout << "Enter Channel Name: ";
				channelName = inputString();
				cout << "\nEnter Weekday: ";
				weekDay = convertToUpperCase(inputString());

				if (channelName != "" && weekDay != "")
				{

					if(box.listByChannel(channelName,convertStringToWeekDay(weekDay)).empty()) 
					{ 
						cout << "\nThere is programs for that channel in that day"; 
						Sleep(1000); 
						break; 
					} 
					else
					{ 
						box.PrintProgramsByChannel(i ,channelName, convertStringToWeekDay(weekDay)); 
						do
						{ 
							unsigned char a = _getch(); 
							if(a == 77) 
							{ 
								i++; 
							} 
							else if(a == 75) 
							{ 
								i=i-1; 
							} 

							else if(a == '1') 
							{ 
								break; 
							} 

							if(i < 0) 
							{ 
								i = box.listByChannel(channelName,convertStringToWeekDay(weekDay)).size()-1; 
							} 
							if(i > box.listByChannel(channelName,convertStringToWeekDay(weekDay)).size()-1) 
							{ 
								i = 0; 
							} 

							box.PrintProgramsByChannel(i,channelName, convertStringToWeekDay(weekDay)); 

						}while(true); 
						break; 
					}

				}

			}

		case '4': // Listagem de programas por tipo
			{
				unsigned int i = 0; 
				string weekDay="";
				string Type="";

				cin.clear();
				ClearScr();


				cout <<"Enter Type (NEWS, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING): ";
				Type = convertToUpperCase(inputString());
				cout << "\nEnter Weekday: ";
				weekDay = convertToUpperCase(inputString());
				if (Type != "" && weekDay != "")
				{

					if(box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay)).empty()) 
					{ 
						cout << "\nThere is no programs for that type"; 
						Sleep(1000); 
						break; 
					} 
					else
					{ 
						box.PrintProgramsByType(i ,convertStringToProgramType(Type),convertStringToWeekDay(weekDay)); 
						do
						{ 
							unsigned char a = _getch(); 
							if(a == 77) 
							{ 
								i++; 
							} 
							else if(a == 75) 
							{ 
								i=i-1; 
							} 

							else if(a == '1') 
							{ 
								break; 
							} 

							if(i < 0) 
							{ 
								i = box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay)).size()-1; 
							} 
							if(i > box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay)).size()-1) 
							{ 
								i = 0; 
							} 

							box.PrintProgramsByType(i ,convertStringToProgramType(Type), convertStringToWeekDay(weekDay)); 

						}while(true); 
						break; 
					}
				}
			}
		case '5':{
			ClearScr();
			cout<< "A total of ";
			box.moneySpent();
			cout<< " was spent renting movies from this movie Club\n";
			Sleep(1000);
				 }

		case '6':
			{
			}
		case '7':
			{
			}
		case '8':
			{
			}
		}
	}while (op != '0');
}