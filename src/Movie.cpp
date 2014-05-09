#include "Movie.h"


Movie::Movie(void)
{

}


Movie::~Movie(void)
{

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