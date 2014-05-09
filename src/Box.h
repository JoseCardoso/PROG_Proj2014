#pragma once
#include <string>
#include <vector>

#include "Channel.h"
#include "Movie.h"
#include "Program.h"
#include "Date.h"

using namespace std;

class Box
{

private:
	string ownerPass;
	Date currentDate;
	vector<Channel*> channels;
	vector<Movie*> movies;
	vector<Movie*> viewedMovies;
	vector<Program*> recordList;


public:
	Box(void);
	Box(string pass , Date date); 
	~Box(void);
	Box(string passwd, Date currentDate);
	vector<Program*> listByDay(WeekDay day) const;
	vector<Program*> listByChannel(string  channel, string day) const;
	vector<Program*> listByType(string  type, string day) const;
	bool rentMovies(string title);
	float moneySpent() const;
	int timesWhatched(string title) const;
	bool changePassword();          // ask, verify and change the password
	// Channel CRUD
	bool createdChanel();
	bool removeChanel();
	bool updateChanel();
	// Program CRUD
	bool createdProgram(string chanel);
	bool removeProgram();
	bool updateProgram();
	// Movie CRUD
	bool createdMovie();
	bool removeMovie();
	bool updateMovie();

};

