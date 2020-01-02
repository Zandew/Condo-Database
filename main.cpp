#include <iostream>
#include "Profile.h"
#include "Driver.h"
#include "Car.h"
#include "Ride.h"

using namespace std;

int main(){
	string name;
	cin >> name;
	cout << name << endl;
	Profile profile(name);
	cout << profile.name << endl;
	return 0;
}
