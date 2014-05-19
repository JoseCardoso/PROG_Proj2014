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

	bool admin = false , login = false;


	unsigned char op;

	do {
		ClearScr();
		if (!admin)
			cout << "                            TV BOX\n\nMenu:\n\n1- Login As Admin\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n\n0- Exit";
		else
			cout << "                            TV BOX\n\nMenu:\n\n1- Login As Admin\n2- List Programs By Day\n3- List Programs By Channel\n4- List Programs By Type\n5- Show Money Spent\n6- Manage TV BOX\n\n0- Exit";

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
				{
						ClearScr();
						cout << "Enter Password: ";
						password = inputString();

						if (password == box.getPassword()){
								login = true;
								admin = true;
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
  
				if(box.listByDay(SUNDAY).empty()) 
                { 
                    cout << "\nThere is no art in this gallery"; 
                    Sleep(1000); 
                    break; 
                } 
                else
                { 
					box.PrintProgramsByDay(0 ,SUNDAY); 
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
							i = box.listByDay(SUNDAY).size()-1; 
                        } 
                        if(i > box.listByDay(SUNDAY).size()-1) 
                        { 
                            i = 0; 
                        } 
  
                       box.PrintProgramsByDay(0 ,SUNDAY); 
  
                    }while(true); 
                    break; 
                }

			}


		}
	}while (op != '0');

}