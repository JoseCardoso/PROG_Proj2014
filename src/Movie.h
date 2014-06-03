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
	void setName(string name);
	void setCost(int cost);
	void setRentedTimes(int rentedTimes);
	void incRented();
	long getRentedTimes();
	double getCost();
};

