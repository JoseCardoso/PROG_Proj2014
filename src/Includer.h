#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <cstdlib>
#include <stdlib.h>    
#include <time.h>      
#include <conio.h>
#include <algorithm>

using namespace std;

enum WeekDay {
	SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY 
};


enum ProgramType {
	NEWS, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING
};


string inputString();
int Value();
void ClearScr();
void hideCursor();
string convertToLowerCase (string Word);
string convertToUpperCase (string Word);
vector <int> parsingInput(string line);
WeekDay convertStringToWeekDay(string day);
string convertWeekDayToString(WeekDay day);
ProgramType convertStringToProgramType(string type);
string convertProgramTypeToString(ProgramType type);
string convertIntToString(int number);
bool checkValidWeekDay(string day);
bool checkValidProgramType(string type);


