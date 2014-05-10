#pragma once

#include "Includer.h"
#include "Date.h"

enum ProgramType {
	NEW, SPORTS, ENTERTAINMENT, LIFE_STYLE, COOKING
};

using namespace std;

class Program
{
private:
	string name;
	ProgramType type;
	bool recorded;
	int duration;
	Date exhibitionDate;
public:
	Program(void);
	Program(string name, ProgramType type, int duration, Date exhibitionDate);
	~Program(void);
	string getName() const;
	Date getDate() const;
	int getDuration() const;
	ProgramType getProgramType() const;
	void setRecorded(bool recorded);
};

