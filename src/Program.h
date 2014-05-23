#pragma once

#include "Includer.h"
#include "Date.h"

using namespace std;

class Program
{
private:
	string name;
	ProgramType type;
	string belongsToTheChannel;
	bool recorded;
	bool toBeRecorded;
	int duration;
	Date exhibitionDate;
public:
	Program(void);
	Program(string name, ProgramType type, int duration, Date exhibitionDate);
	~Program(void);
	string getBelongsToChannel() const;
	void setBelongsToChannel(string belongsToTheChannel);
	string getName() const;
	Date getDate() const;
	bool getRecorded() const;
	bool getToBeRecorded() const;
	void setToBeRecorded(bool toBeRecorded);
	int getDuration() const;
	ProgramType getProgramType() const;
	void setRecorded(bool recorded);
	bool operator<(Program p)
	{
		return exhibitionDate < p.exhibitionDate;
	}
};

