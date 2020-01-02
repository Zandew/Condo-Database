#include <iostream>
#include <vector>
#include "Profile.h"
#include "Ride.h"
#include "Driver.h"

using namespace std;

Profile::Profile(string name){
	Profile::name = name;
	Profile::balance = 0;
}

Profile::~Profile(){

}

void Profile::addRide(Ride ride){
	Profile::rides.push_back(ride);
}

void Profile::payRide(int idx){
	
}

void Profile::showProfile(){
	cout << name << endl;
}
