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



	void Movie::setName(string name){
		this->name = name;
	}
	void Movie::setCost(int cost){
		this->cost = cost;
	}
	void Movie::setRentedTimes(int rentedTimes){
		this->rentedTimes = rentedTimes;
	}