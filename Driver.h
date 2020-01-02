#pragma once
#include "Profile.h"

class Car;

class Driver : protected Profile{
	private:
		Car car;
		double rating, rate;
	public:
		Driver(Car car, double rating, double rate);
		~Driver();
		void showProfile();
};
