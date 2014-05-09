#pragma once

#include <string>
#include <vector>
#include "Program.h"



using namespace std;
class Channel
{
private:
	string name;
	vector<Program*> programs;
public:
	Channel(void);
	~Channel(void);
	vector <Program*> getPrograms();
};

