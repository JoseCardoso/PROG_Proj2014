#include "Movie.h"


Movie::Movie(void)
{

}


Movie::~Movie(void)
{

}
Movie::Movie(string name, double cost)
{
	this->name = name;
	this->cost = cost;
	this->rentedTimes = 0;
}

string Movie:: getName()
{
	return name;
}

void Movie:: incRented()
{
	rentedTimes++;
}

long Movie:: getRentedTimes()
{
	return rentedTimes;
}

double Movie::getCost()
{
	return cost;
}