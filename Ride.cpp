#include "Ride.h"
#include "Driver.h"

Ride::Ride(Driver driver, string source, string destination){
	Ride::driver = driver;
	Ride::source = source;
	Ride::destination = destination;
}

Ride::~Ride(){

}
