#pragma once

#include "Includer.h"
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
	bool adminLogin;
	vector<Channel*> channels;
	vector<Movie*> movies;
	vector<Movie*> viewedMovies;
	vector<Program*> recordList;


public:
	Box(void);
	Box(string pass , Date date); 
	~Box(void);
	bool getAdminLogin() const;
	void setAdminLogin(bool login);
	vector<Program*> listByDay(WeekDay day) const;
	vector<Program*> listByChannel(string  channel, WeekDay day) const;
	vector<Program*> listByType(ProgramType  type, WeekDay day) const;
	bool rentMovies(string title);
	float moneySpent() const;
	int timesWhatched(string title) const;
	string getPassword() const;
	bool changePassword();          // ask, verify and change the password
	void PrintProgramsByDay(int i,WeekDay day);
	void PrintProgramsByChannel(int i,string channel, WeekDay day);
	void PrintProgramsByType(int i, ProgramType type, WeekDay day);
	void PrintMovies(int i);
	void PrintAllPrograms(int i);
	void PrintAllChannels(int i);
	// Channel CRUD
	bool createdChanel();
	bool removeChanel(int i);
	bool updateChanel(char op);
	// Program CRUD
	bool createdProgram(int i); //i significa o indice do channel no vector de canais da Box
	bool removeProgram(int i); //i significa o indice do programa no vector de programas para poder remove-lo dos respectivos canais
	bool updateProgram(char op);
	// Movie CRUD
	bool createdMovie();
	bool removeMovie(int i);
	bool updateMovie(char op);

};


