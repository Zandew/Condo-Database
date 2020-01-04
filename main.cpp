#include <iostream>
#include "Profile.h"
#include "Driver.h"
#include "Car.h"
#include "Ride.h"

using namespace std;

int main(){
	cout << "CREATE ACCOUNT" << endl;
	cout << "Enter Your Name: " << endl;
	string name;
	cin >> name;
	Profile profile(name);
	return 0;
}
