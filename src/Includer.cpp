#include "Includer.h"

string convertToLowerCase (string Word){ //Function to do a case-insensitive search

	for (unsigned int i = 0; i < Word.size(); i++){
		Word[i] = tolower(Word[i]);
	}
	return Word;
}

void ClearScr()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}


string inputString()
{
	string nomestring;
	ClearScr();
	ws(cin); //ignorar espaço antes de introduzir nome
	getline(cin, nomestring);
	if (nomestring.length() > 21)
	{
		ClearScr();
		cout << "Please write only first and last name.";
		Sleep(800);
		return inputString();
	}
	return nomestring;
}

int Value()
{

	ClearScr();
	int out;
	string in;
	while(true) {

		cout << "Enter a valid value: ";
		cin.ignore();
		getline(cin,in);
		stringstream ss(in); //covert input to a stream for conversion to int

		if(ss >> out && !(ss >> in)) return out;

		cin.clear();
		cerr << "\nInvalid input. Please try again.\n";
		Sleep(800);
	}
}

void hideCursor()
{
	CONSOLE_CURSOR_INFO cci = {100, FALSE};

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

vector <int> parsingInput(string line)
{
	vector <int> IDs;
	stringstream stream(line);

	while (1) {
		int n;
		stream >> n;
		if (!stream)
			break;
		else
			IDs.push_back(n);
	}

	return IDs;

}

ProgramType convertStringToProgramType(string type)
{
	if (type == "NEWS")
		return NEWS;
	else if (type == "ENTERTAINMENT")
		return ENTERTAINMENT;
	else if (type == "LIFE_STYLE")
		return LIFE_STYLE;
	else if (type == "COOKING")
		return COOKING;
	else if (type == "SPORTS")
		return SPORTS;

}

string convertProgramTypeToString(ProgramType type)
{
	if (type == NEWS)
		return "NEWS";
	else if (type == ENTERTAINMENT)
		return "ENTERTAINMENT";
	else if (type == LIFE_STYLE)
		return "LIFE_STYLE";
	else if (type == COOKING)
		return "COOKING";
	else if (type == SPORTS)
		return "SPORTS";
}

WeekDay convertStringToWeekDay(string day)
{
	if (day == "SUNDAY")
		return SUNDAY;
	else if (day == "MONDAY")
		return MONDAY;
	else if (day == "TUESDAY")
		return TUESDAY;
	else if (day == "WEDNESDAY")
		return WEDNESDAY;
	else if (day == "THURSDAY")
		return THURSDAY;
	else if (day == "FRIDAY")
		return FRIDAY;
	else if (day == "SATURDAY")
		return SATURDAY;	
}

string convertWeekDayToString (WeekDay day)
{
	if (day = SUNDAY)
		return "SUNDAY";
	else if (day = MONDAY)
		return "MONDAY";
	else if (day = TUESDAY)
		return "TUESDAY";
	else if (day = WEDNESDAY)
		return "WEDNESDAY";
	else if (day = THURSDAY)
		return "THURSDAY";
	else if (day = FRIDAY)
		return "FRIDAY";
	else if (day = SATURDAY)
		return "SATURDAY";
}

string convertIntToString(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}