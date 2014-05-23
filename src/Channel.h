#pragma once

#include "Includer.h"
#include "Program.h"



using namespace std;
class Channel
{
private:
	string name;
	vector<Program*> programs;
public:
	Channel(void);
	Channel(string name);
	void addProgram(Program* program);
	void removeProgram(string programName);
	~Channel(void);
	vector <Program*> getPrograms() const;
	string getName() const;
	void setName(string name);
	bool CheckIfValidTimeForNewProgram(Program* p);
};