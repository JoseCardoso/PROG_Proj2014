#pragma once

#include <string>

using namespace std;

class Movie
{
private:
	string name;
	double cost;
	long rentedTimes;
public:
	Movie(void);
	~Movie(void);
	string getName();
	void incRented();
	long getRentedTimes();
	double getCost();
};

