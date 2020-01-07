#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct Car{
	string model, license;
	int seats;
};

class Driver{
	private:
		string name;
		Car car;
		double rating, rate;
	public:
		Driver(string name, Car car, double rating, double rate);
		void showInfo();
};

Driver::Driver(string name, Car car, double rating, double rate){
	Driver::name = name;
	Driver::car = car;
	Driver::rating = rating;
	Driver::rate = rate;
};

void Driver::showInfo(){
}

class Ride{
	protected:
		Driver driver;
		string source, destination;
	public:
		Ride(Driver driver, string source, string destination);
		void showInfo();
};

class Carpool : protected Ride{
	private:
		int passengers;
	public:
		Carpool(Driver driver, string source, string destination, int passengers);
		void showInfo();
};

class Profile {
	private:
		string name;
		double balance;
		vector<Ride> rides;
	public:
		void setName(string name);
		string getName();
		void setBalance(double balance);
		double getBalance();
		void addRide(Ride ride);
		void showRides();
		void payRide(int idx);
} profile;

void Profile::setName(string name){
	Profile::name = name;
}

string Profile::getName(){
	return Profile::name;
}

void Profile::setBalance(double balance){
	Profile::balance = balance;
}

double Profile::getBalance(){
	return Profile::balance;
}


void Profile::addRide(Ride ride){
	Profile::rides.push_back(ride);
}

void Profile::showRides(){
}

void Profile::payRide(int idx){
}

class Screen{
	public:
		virtual bool showScreen() = 0;
};

class MenuScreen : public Screen{
	public:
		bool showScreen();
};

class ProfileScreen : public Screen{
	public:
	   	bool showScreen();
};

class RideScreen : public Screen{
	public:
		bool showScreen();
};

Screen *arr[3] = {new MenuScreen, new ProfileScreen, new RideScreen};
Screen **currentScreen = arr;

bool MenuScreen::showScreen(){
    cout << "----------MENU----------" << endl;
    cout << "0->Exit" << endl;
    cout << "1->Profile" << endl;
    cout << "2->Reserve Ride" << endl;
	int x;
	cin >> x;
	if (x==0) return false;
	else if (x==1) currentScreen = arr+1;
	else currentScreen = arr+2;
	return true;
}

bool ProfileScreen::showScreen(){
	cout << "----------PROFILE----------" << endl;
    cout << "Name: " << profile.getName() << endl;
   	cout << "Balance: $" << fixed << setprecision(2) << profile.getBalance() << endl;
    cout << "Ride History: " << endl;
	return true;
}

bool RideScreen::showScreen(){
	cout << "RIDESCREEN" << endl;
}

int main(){
	cout << "CREATE ACCOUNT" << endl;
	cout << "Enter Your Name: ";
	string name;
	getline(cin, name);
	profile.setName(name);
	while ((*currentScreen)->showScreen());
	return 0;
}
