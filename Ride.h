#include <iostream>
#include "Driver.h"

class Ride{
	private:
		Driver driver;
		string source, destination;
	public:
		Ride(Driver driver, string source, string destination);
		~Ride();
}
