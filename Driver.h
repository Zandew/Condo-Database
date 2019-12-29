#include<Profile.h>
#include<Car.h>

class Driver : protected Profile{
	private:
		Car car;
		double rating;
};
