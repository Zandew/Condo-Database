#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Ride;

class Profile{
	protected:
		string name;
		double balance;
		vector<Ride> rides;
	public:
		Profile(string name);
		~Profile();
		void addRide(Ride ride);
		void payRide(int idx);
};
