#pragma once

#include "Includer.h"


class Movie
{
private:
	string name;
	double cost;
	long rentedTimes;
public:
	Movie(void);
	Movie(string name, double cost);
	~Movie(void);
	string getName();
	void incRented();
	long getRentedTimes();
	double getCost();
};

