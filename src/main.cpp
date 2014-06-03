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

int main(){
	srand(time(NULL));
	//need to load from file, for now password will be 1234
	Box box = Box("", currentDate());
	box.loadGeneralInfo();
	box.loadMovies();
	box.loadChannels();
	box.loadPrograms();

	hideCursor();

	bool login = false;


	unsigned char op;

	do {
		ClearScr();
		cout<<"                            TV BOX\n" << box.getCurrentDate().PrintDate() << endl;
		if (!box.getAdminLogin())
			cout << "\nMenu:\n\n1- Login As Admin\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n6- Movie Club\n\n0- Exit";
		else
			cout << "\nMenu:\n\n1- Change PassWord\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n6- Movie Club\n7- Manage Programs\n8- Manage Channels\n9- Logout \n\n0- Exit";

		op = _getch();
		switch (op) {
		case '0'://Exit
			{

				box.saveMovies();
				box.saveGeneralInfo();
				box.saveMovies();
				box.savePrograms();

				return 0;
			}
		case '1'://Login as admin
			{ if (box.getAdminLogin())
			{
				box.changePassword();
				Sleep(800);
			}
			else{
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
			}
			break;


			}
		case '2': // Listagem de programas por dia
			{
				unsigned int i = 0; 

				string weekDay = convertWeekDayToString(box.getCurrentDate().getDay());

				cin.clear();
				ClearScr();

				cout << "Enter Weekday: ";
				weekDay = convertToUpperCase(inputString());

				if (checkValidWeekDay(weekDay))
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
								if (box.listByDay(convertStringToWeekDay(weekDay))[i]->getRecorded() == true)
								{
									if (box.listByDay(convertStringToWeekDay(weekDay))[i]->getToBeRecorded() == true){
										cout<< "Program is already set to be recorded\n";
										Sleep(800);
									}
									else
									{
										box.listByDay(convertStringToWeekDay(weekDay))[i]->setToBeRecorded(true);
									}

								}
								else
								{
									cout<< "Program is already recorded\n";
									Sleep(800);
								} 
							} 

							else if(a == '0') 
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
				else
				{
					cout << "\nInvalid Entry";
					Sleep(800);
					break;
				}

			}
		case '3': // Listagem de programas por Canal
			{
				unsigned int i = 0; 
				string channelName="";
				string weekDay=convertWeekDayToString(box.getCurrentDate().getDay());

				cin.clear();
				ClearScr();
				cout << "Enter Channel Name: ";
				channelName = inputString();
				cout << "\nEnter Weekday: ";
				weekDay = convertToUpperCase(inputString());

				if (channelName != "" && checkValidWeekDay(weekDay))
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
								if (box.listByChannel(channelName,convertStringToWeekDay(weekDay))[i]->getRecorded() == true)
								{
									if (box.listByChannel(channelName,convertStringToWeekDay(weekDay))[i]->getToBeRecorded() == true){
										cout<< "Program is already set to be recorded\n";
										Sleep(800);
									}
									else
									{
										box.listByChannel(channelName,convertStringToWeekDay(weekDay))[i]->setToBeRecorded(true);
									}

								}
								else
								{
									cout<< "Program is already recorded\n";
									Sleep(800);
								}

								break; 
							} 

							else if(a == '0') 
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
				else
				{
					cout << "\nInvalid Entry";
					Sleep(800);
					break;
				}

			}

		case '4': // Listagem de programas por tipo
			{
				unsigned int i = 0; 
				string weekDay=convertWeekDayToString(box.getCurrentDate().getDay());
				string Type="";

				cin.clear();
				ClearScr();


				cout <<"Enter Type (NEWS, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING): ";
				Type = convertToUpperCase(inputString());
				cout << "\nEnter Weekday: ";
				weekDay = convertToUpperCase(inputString());
				if (checkValidProgramType(Type) && checkValidWeekDay(weekDay))
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
								if (box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay))[i]->getRecorded() == true)
								{
									if (box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay))[i]->getToBeRecorded() == true){
										cout<< "Program is already set to be recorded\n";
										Sleep(800);
									}
									else
									{
										box.listByType(convertStringToProgramType(Type) ,convertStringToWeekDay(weekDay))[i]->setToBeRecorded(true);
									}

								}
								else
								{
									cout<< "Program is already recorded\n";
									Sleep(800);
								}
								break; 
							} 

							else if(a == '0') 
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
				else
				{
					cout << "\nInvalid Entry";
					Sleep(800);
					break;
				}
			}
		case '5':
			{
				ClearScr();
				cout<< "A total of " << box.moneySpent() <<" Euros were spent renting movies from this movie Club\n";
				Sleep(2000);
			}

			break;

		case '6':
			{
				unsigned int i = 0; 
				if(box.getMovies().empty() && box.getViewedMovies().empty()) 
				{ 
					cout << "\nThere is no movies in the movie club"; 
					Sleep(1000); 
					break; 
				} 
				else
				{ 
					box.PrintMovies(i); 
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
							box.rentMovies(box.getAllMovies()[i]->getName());
							break; 
						} 
						else if(a == '2') 
						{ 
							if (box.getAdminLogin())
							{
								box.updateMovie('2', i);
							}
							break; 
						} 
						else if(a == '3') 
						{ 
							if (box.getAdminLogin())
							{
								box.updateMovie('3',i);
							}
							break; 
						} 

						else if(a == '4') 
						{ 
							if (box.getAdminLogin())
							{
								box.createdMovie();
							}
							break; 
						} 
						else if(a == '5') 
						{ 
							if (box.getAdminLogin())
							{
								box.removeMovie(i);
							}
							break; 
						} 

						else if(a == '0') 
						{ 
							break; 
						} 


						if(i < 0) 
						{ 
							i = box.getAllMovies().size()-1; 
						} 
						if(i > box.getAllMovies().size()-1) 
						{ 
							i = 0; 
						} 

						box.PrintMovies(i);

					}while(true); 
					break; 
				}
			}
		case '7':
			{
				if (box.getAdminLogin()){	
					unsigned int i = 0; 
					if(box.getRecordList().empty()) 
					{ 
						cout << "\nThere is no programs in this TV box"; 
						Sleep(1000); 
						break; 
					} 
					else
					{ 
						box.PrintAllPrograms(i); 
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
								box.updateProgram('1',i);
								break; 
							} 
							else if(a == '2') 
							{ 

								box.updateProgram('2',i);
								break; 
							} 
							else if(a == '3') 
							{ 
								box.updateProgram('3',i);
								break; 
							} 

							else if(a == '4') 
							{ 
								box.updateProgram('4',i);

								break; 
							} 

							else if(a == '0') 
							{ 
								break; 
							} 

							if(i < 0) 
							{ 
								i = box.getRecordList().size()-1; 
							} 
							if(i > box.getRecordList().size()-1) 
							{ 
								i = 0; 
							} 

							box.PrintAllPrograms(i);

						}while(true); 
						break; 
					}
				}
			}
		case '8':
			{

				if (box.getAdminLogin()){	
					unsigned int i = 0; 
					if(box.getChannels().empty()) 
					{ 
						cout << "\nThere is no Channels in this TV box"; 
						Sleep(1000); 
						break; 
					} 
					else
					{ 
						box.PrintAllChannels(i); 
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
								box.updateChanel('1',i);
								break; 
							} 
							else if(a == '2') 
							{ 

								box.updateChanel('2',i);
								break; 
							} 
							else if(a == '3') 
							{ 
								box.updateChanel('3',i);
								break; 
							} 

							else if(a == '4') 
							{ 
								box.createdChanel();

								break; 
							} 

							else if(a == '5') 
							{ 
								box.removeChanel(i);

								break; 
							} 

							else if(a == '0') 
							{ 
								break; 
							} 

							if(i < 0) 
							{ 
								i = box.getChannels().size()-1; 
							} 
							if(i > box.getChannels().size()-1) 
							{ 
								i = 0; 
							} 

							box.PrintAllChannels(i);

						}while(true); 
						break; 
					}
				}
			}
		case '9':
			{
				if (box.getAdminLogin())
				{
					box.setAdminLogin(false);
					login = false;

					break;
				}
			}
		}
	}while (op != '0');


}
