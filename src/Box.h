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
	vector<Movie* > getMovies();
	vector<Movie*> getViewedMovies();
	vector<Program*> getRecordList();
	vector<Channel*> getChannels();
	vector<Movie*> getAllMovies();
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
	Date getCurrentDate();
	// Channel CRUD
	void createdChanel();
	void removeChanel(int i);
	void updateChanel(char op, int i);
	bool checkNewChannelName(string name);
	// Program CRUD
	void createdProgram(int i); //i significa o indice do channel no vector de canais da Box
	void removeProgram(int i); //i significa o indice do programa no vector de programas para poder remove-lo dos respectivos canais
	void updateProgram(char op, int i);// como acima
	bool checkNewProgramName(string name);
	// Movie CRUD
	void createdMovie();
	void removeMovie(int i);
	void updateMovie(char op, int i);
	bool checkNewMovieName(string name);
	// Load and Save
	void saveGeneralInfo();
	void loadGeneralInfo();
	void saveChannels();
	void loadChannels();
	void savePrograms();
	void loadPrograms();
	void saveMovies();
	void loadMovies();
};


