#include <iostream>
#include <cstdlib>
#include <algorithm>
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
    Driver() {}
    Driver(string name, Car car, double rate);
    string getName();
    Car getCar();
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

Car Driver::getCar(){
    return Driver::car;
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
    virtual void select();
    void setTime(time_t time);
    time_t getTime();
    void setPaid(bool paid);
    bool getPaid();
    virtual void showInfo();
    virtual void showHistory();
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

void Ride::select(){
    driver->showInfo();
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

void Ride::showHistory(){
    cout << setw(15) << driver->getName() << setw(10) << source << setw(14) << destination << "$" << fixed << setprecision(2) << setw(8) << driver->getPrice(20) << setw(10) << (paid?"Paid":"Not Paid") << put_time(localtime(&time), "%Y/%m/%d %T") << endl;
}

class Carpool : public Ride{
private:
    int passengers;
public:
    Carpool(Driver* driver, string source, string destination, int passengers);
    void select();
    void showInfo();
	void showHistory();
};
Carpool::Carpool(Driver* driver, string source, string destination, int passengers){
    Carpool::driver = driver;
    Carpool::source = source;
    Carpool::destination = destination;
    Carpool::passengers = passengers;
}

void Carpool::select(){
    driver->showInfo();
    cout << "Other Passengers: " << passengers << endl;
}

void Carpool::showInfo(){
    cout << driver->getName() << " " <<  setw(14-driver->getName().length()) << "(CP)" << fixed << setprecision(1) << setw(8) << driver->getRating() << "$" << driver->getPrice(20) << endl;
}

void Carpool::showHistory(){
    cout << driver->getName() << " " << setw(14-driver->getName().length()) << "(CP)" << setw(10) << source << setw(14) << destination << "$" << fixed << setprecision(2) << setw(8) << driver->getPrice(20) << setw(10) << (paid?"Paid":"Not Paid") << put_time(localtime(&time), "%Y/%m/%d %T") << endl;
}


class Profile {
private:
    string name;
    double balance;
    vector<Ride*> rides;
public:
    void setName(string name);
    string getName();
    void setBalance(double balance);
    double getBalance();
    vector<Ride*> getRides();
    void addRide(Ride *ride);
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

vector<Ride*> Profile::getRides(){
    return Profile::rides;
}

void Profile::addRide(Ride *ride){
    ride->setTime(time(NULL));
    ride->setPaid(false);
    Profile::rides.insert(Profile::rides.begin(), ride);
}

void Profile::payRide(int idx){
    Profile::balance -= rides[idx]->getDriver()->getPrice(20);
    rides[idx]->setPaid(true);
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
Car carList[5] = {{"Toyota Corolla", "QBXNB9", 5}, {"Honda Civic", "O5UXPV", 4}, {"Chevrolet Equinox", "AWST5W", 5}, {"Ford F-150", "PBL2SH", 5}, {"Nissan Rogue", "I2OIJ0", 4}};
string nameList[20] = {"James", "John", "Robert", "Michael", "William", "David", "Richard", "Joseph", "Thomas", "Charles", "Mary", "Patricia", "Irene", "Jennifer", "Linda", "Elizabeth", "Barbara", "Susan", "Jessica", "Sarah"};
Driver driverList[10];
Ride *rides[5];

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
        cout << "Enter the source and destination of the ride: ";
        string source, destination;
        cin >> source >> destination;
        random_shuffle(driverList, driverList+10);
        for (int i=0; i<5; i++) {
            if (!(rand()%5)) rides[i] = new Carpool(&driverList[i], source, destination, rand()%driverList[i].getCar().seats);
            else rides[i] = new Ride(&driverList[i], source, destination);
        }
    }
    return true;
}

bool ProfileScreen::showScreen(){
    cout << "----------PROFILE----------" << endl;
    cout << "Name: " << profile.getName() << endl;
    cout << "Balance: $" << fixed << setprecision(2) << profile.getBalance() << endl;
    cout << "Ride History: " << endl;
    cout << "   " << setfill(' ') << setw(15) << "NAME" << setw(10) << "SOURCE" << setw(14) << "DESTINATION" << setw(9) << "PRICE" << setw(10) << "STATUS" << "DATE" << endl;
    vector<Ride*> rideHistory = profile.getRides();
    for (int i=0; i<rideHistory.size(); i++){
        cout << (i+1) << ". ";
        rideHistory[i]->showHistory();
    }
    cout << "Return to main menu(0) or pay for ride(ride #) or add money(-1)? ";
    int idx;
    cin >> idx;
    int sz = rideHistory.size();
    while (idx<-1||idx>sz||(idx>0&&idx<=sz&&rideHistory[idx-1]->getDriver()->getPrice(20)>profile.getBalance())){
        if (idx>0&&idx<=sz) {
            if (rideHistory[idx-1]->getPaid()) cout << "Already paid for this ride" << endl;
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
        rideHistory[idx-1]->getDriver()->addRating(rating);
    }
    return true;
}

bool RideScreen::showScreen(){
    cout << "----------RIDES----------" << endl;
    cout << "#  " << setw(15) << "NAME" << "RATING" << "  PRICE" << endl;
    cout << setfill(' ');
    for (int i=0; i<5; i++){
        cout << (i+1) << ". ";
        rides[i]->showInfo();
    }
    cout << "Return to main menu(0) or view a ride(ride #)? ";
    int idx, com;
    cin >> idx;
    while (idx<0||idx>5){
        cout << "Invalid command" << endl;
        cout << "Return to main menu(0) or view a ride(ride #)? ";
        cin >> idx;
    }
    if (idx==0){
        currentScreen = arr;
    }else{
        rides[--idx]->select();
        cout << "Choose this ride(0) or go back(1)? ";
        cin >> com;
        while (com<0||com>1){
            cout << "Invalid command" << endl;
            cout << "Choose this ride(0) or go back(1)? ";
            cin >> com;
        }
        if (com==0){
            if (!profile.getRides().empty()&&!profile.getRides()[0]->getPaid()){
                cout << "You have not paid for your last ride" << endl;
            }else{
                profile.addRide(rides[idx]);
                currentScreen = arr;
            }
        }
    }
    return true;
}

void init(){
    cout << left;
    cout << "CREATE ACCOUNT" << endl;
    cout << "Enter Your Name: ";
    string name;
    getline(cin, name);
    profile.setName(name);
    srand(time(nullptr));
    bool used[20];
    for (int i=0; i<10; i++){
        int idx = rand()%20;
        while (used[idx]) idx = rand()%20;
        driverList[i] = {nameList[idx], carList[rand()%5], (double) (rand()%10)+1};
        int ratings = rand()%5;
        for (int j=0; j<ratings; j++) driverList[i].addRating(rand()%10);
        used[idx] = true;
    }
}

int main(){
    init();
    while ((*currentScreen)->showScreen());
    return 0;
}
