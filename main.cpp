#include <iostream>
#include "Profile.h"
#include "Driver.h"
#include "Car.h"
#include "Ride.h"
#include "Screen.h"
#include "MenuScreen.h"
#include "ProfileScreen.h"
#include "RideScreen.h"

using namespace std;

int main(){
	cout << "CREATE ACCOUNT" << endl;
	cout << "Enter Your Name: " << endl;
	string name;
	cin >> name;
	Profile profile(name);
	Screen *arr[3];
	arr[0] = new MenuScreen;
	arr[1] = new ProfileScreen;
	arr[2] = new RideScreen;
	for (int i=0; i<3; i++){
		arr[i]->showScreen();
	}
	return 0;
}
