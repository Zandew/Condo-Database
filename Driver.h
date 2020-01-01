#include "Profile.h"
#include "Car.h"

class Driver : protected Profile{
	private:
		Car car;
		double rating, rate;
	public:
		Driver(Car car, double rating, double rate);
		~Driver();
};
