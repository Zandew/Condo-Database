#pragma once
#include <iostream>

class Driver;

class Ride{
	private:
		Driver driver;
		string source, destination;
	public:
		Ride(Driver driver, string source, string destination);
		~Ride();
};
