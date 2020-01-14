#include <iostream>
#include <ctime>
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
    vector<double> ratings;
    double rate;
public:
    Driver(string name, Car car, double rate);
    string getName();
    string getRating();
    void addRating(double rating);
    double getPrice(double distance);
    void showInfo();
};

Driver::Driver(string name, Car car, double rate){
    Driver::name = name;
    Driver::car = car;
    Driver::rate = rate;
};

string Driver::getName(){
    return Driver::name;
}

string Driver::getRating(){
    if (Driver::ratings.empty()) return "N/A";
    double avg = 0;
    for (double rat : Driver::ratings){
        avg += rat;
    }
    avg /= Driver::ratings.size();
    return to_string(avg).substr(0, 3);
}

void Driver::addRating(double rating){
    Driver::ratings.push_back(rating);
}

double Driver::getPrice(double distance){
    return Driver::rate*distance;
}

void Driver::showInfo(){
    cout << setfill('-') << setw(20) << "-" << endl;
    cout << "Name: " << Driver::name << endl;
    cout << "Car model: " << Driver::car.model << endl;
    cout << "Seats: " << Driver::car.seats << endl;
    cout << "License plate: " << Driver::car.license << endl;
    cout << "Rating: " << fixed << setprecision(1) << getRating() << "/10.0" << endl;
    cout << setw(20) << "-" << endl;
}

class Ride{
protected:
    Driver *driver;
    string source, destination;
    time_t time;
    bool paid;
public:
    Ride(){}
    Ride(Driver *driver, string source, string destination);
    Driver* getDriver();
    string getSource();
    string getDestination();
    void setTime(time_t time);
    time_t getTime();
    void setPaid(bool paid);
    bool getPaid();
    void showInfo();
};

Ride::Ride(Driver *driver, string source, string destination){
    Ride::driver = driver;
    Ride::source = source;
    Ride::destination = destination;
}

Driver* Ride::getDriver(){
    return Ride::driver;
}

string Ride::getSource(){
    return Ride::source;
}

string Ride::getDestination(){
    return Ride::destination;
}

void Ride::setTime(time_t time){
    Ride::time = time;
}

time_t Ride::getTime(){
    return Ride::time;
}

void Ride::setPaid(bool paid){
    Ride::paid = paid;
}

bool Ride::getPaid(){
    return Ride::paid;
}

void Ride::showInfo(){
    cout << setw(15) << driver->getName() << fixed << setprecision(1) << setw(8) << driver->getRating() << "$" << driver->getPrice(20) << endl;
}

class Carpool : protected Ride{
private:
    int passengers;
public:
    Carpool(Driver* driver, string source, string destination, int passengers);
    void showInfo();
};
Carpool::Carpool(Driver* driver, string source, string destination, int passengers){
    Carpool::driver = driver;
    Carpool::source = source;
    Carpool::destination = destination;
    Carpool::passengers = passengers;
}

void Carpool::showInfo(){
    cout << setw(15) << driver->getName() << "*" << fixed << setprecision(1) << setw(8) << driver->getRating() << "$" << driver->getPrice(20) << endl;
}

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
    vector<Ride> getRides();
    void addRide(Ride ride);
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

vector<Ride> Profile::getRides(){
    return Profile::rides;
}

void Profile::addRide(Ride ride){
    ride.setTime(time(NULL));
    ride.setPaid(false);
    Profile::rides.insert(Profile::rides.begin(), ride);
}

void Profile::payRide(int idx){
    Profile::balance -= rides[idx].getDriver()->getPrice(20);
    rides[idx].setPaid(true);
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
Car car = {"toyota", "M2N6W5", 5};
Driver d1 = {"Andrew", car, 5};
Driver d2 = {"Michel", car, 6};
vector<Ride> rides;

bool MenuScreen::showScreen(){
    cout << "----------MENU----------" << endl;
    cout << "0->Exit" << endl;
    cout << "1->Profile" << endl;
    cout << "2->Reserve Ride" << endl;
    int x;
    cin >> x;
    if (x==0) return false;
    else if (x==1) currentScreen = arr+1;
    else {
        currentScreen = arr+2;
        rides.clear();
        cout << "Enter the source and destination of the ride: ";
        string source, destination;
        cin >> source >> destination;
        rides.push_back(Ride(&d1, source, destination));
        rides.push_back(Ride(&d2, source, destination));
    }
    return true;
}

bool ProfileScreen::showScreen(){
    cout << "----------PROFILE----------" << endl;
    cout << "Name: " << profile.getName() << endl;
    cout << "Balance: $" << fixed << setprecision(2) << profile.getBalance() << endl;
    cout << "Ride History: " << endl;
    cout << "   " << setfill(' ') << setw(10) << "NAME";
    cout << setw(10) << "SOURCE";
    cout << setw(14) << "DESTINATION";
    cout << setw(9) << "PRICE";
    cout << "STATUS" << endl;
    vector<Ride> rideHistory = profile.getRides();
    for (int i=0; i<rideHistory.size(); i++){
        cout << (i+1) << ". " << setw(10) << rideHistory[i].getDriver()->getName();
        cout <<	setw(10) << rideHistory[i].getSource();
        cout << setw(14) << rideHistory[i].getDestination();
        cout << "$" << fixed << setprecision(2) << setw(8) << rideHistory[i].getDriver()->getPrice(20);
        cout << (rideHistory[i].getPaid()?"Paid":"Not Paid") << endl;
    }
    cout << "Return to main menu(0) or pay for ride(ride #) or add money(-1)? ";
    int idx;
    cin >> idx;
    int sz = rideHistory.size();
    while (idx<-1||idx>sz||(idx>0&&idx<=sz&&rideHistory[idx-1].getDriver()->getPrice(20)>profile.getBalance())){
        if (idx>0&&idx<=sz) {
            if (rideHistory[idx-1].getPaid()) cout << "Already paid for this ride" << endl;
            else cout << "Insufficient funds" << endl;
        }else cout <<"Invalid Command" << endl;
        cout << "Return to main menu(0) or pay for ride(ride #)? ";
        cin >> idx;
    }
    if (idx==-1){
        cout << "Enter an amount: ";
        double val;
        cin >> val;
        profile.setBalance(profile.getBalance()+val);
    }else if (idx==0){
        currentScreen = arr;
    }else{
        profile.payRide(idx-1);
        cout << "On a scale of 1 to 10, how did you enjoy this ride? ";
        double rating;
        cin >> rating;
        while (rating<1||rating>10){
            cout << "Invalid Rating" << endl;
            cout << "On a scale of 1 to 10, how did you enjoy this ride? ";
            cin >> rating;
        }
        rideHistory[idx-1].getDriver()->addRating(rating);
    }
    return true;
}

bool RideScreen::showScreen(){
    cout << "----------RIDES----------" << endl;
    cout << "#  " << setw(15) << "NAME" << "RATING" << "  PRICE" << endl;
    cout << setfill(' ');
    for (int i=0; i<rides.size(); i++){
        cout << (i+1) << ". ";
        rides[i].showInfo();
    }
    cout << "Return to main menu(0) or view a ride(ride #)? ";
    int idx, com;
    cin >> idx;
    while (idx<0||idx>rides.size()){
        cout << "Invalid command" << endl;
        cout << "Return to main menu(0) or view a ride(ride #)? ";
        cin >> idx;
    }
    if (idx==0){
        currentScreen = arr;
    }else{
        rides[--idx].getDriver()->showInfo();
        cout << "Choose this ride(0) or go back(1)? ";
        cin >> com;
        while (com<0||com>1){
            cout << "Invalid command" << endl;
            cout << "Choose this ride(0) or go back(1)? ";
            cin >> com;
        }
        if (com==0){
			if (!profile.getRides().empty()&&!profile.getRides()[0].getPaid()){
				cout << "You have not paid for your last ride" << endl;
			}else{
            	profile.addRide(rides[idx]);
            	currentScreen = arr;
			}
        }
    }
    return true;
}

int main(){
    cout << left;
    cout << "CREATE ACCOUNT" << endl;
    cout << "Enter Your Name: ";
    string name;
    getline(cin, name);
    profile.setName(name);
    while ((*currentScreen)->showScreen());
    return 0;
}
