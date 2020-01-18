/*
 * Andrew Xue
 * January 20, 2020
 * ICS4U1-01 Midterm Project
 * Ride-Share Application
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

//Car struct to model Driver's car
struct Car{
    string model, license;
    int seats;
};

//Driver class that stores driver's name, car, ratings and rate
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
    double getPrice();
    void showInfo();
};

//Driver class constructor
Driver::Driver(string name, Car car, double rate){
    Driver::name = name;
    Driver::car = car;
    Driver::rate = rate;
};

//Driver class name getter method
string Driver::getName() {return Driver::name;}

//Driver class car getter method
Car Driver::getCar() {return Driver::car;}

//Driver class method that calculates driver's rating
string Driver::getRating(){
    //if driver has no ratings, no rating availible
    if (Driver::ratings.empty()) return "N/A";
    double avg = 0;
    for (double rat : Driver::ratings){
        avg += rat;
    }
    avg /= Driver::ratings.size();
    //returns average of all driver's ratings
    return to_string(avg).substr(0, 3);
}

//Driver class method to add rating to driver
void Driver::addRating(double rating) {Driver::ratings.push_back(rating);}

//Driver class price getter method
double Driver::getPrice() {return Driver::rate;}

//Driver class method that prints out driver's info
void Driver::showInfo(){
    for (int i=0; i<20; i++) cout << "-";
    cout << "\nName: " << Driver::name << endl;
    cout << "Car model: " << Driver::car.model << endl;
    cout << "Seats: " << Driver::car.seats << endl;
    cout << "License plate: " << Driver::car.license << endl;
    cout << "Rating: " << fixed << setprecision(1) << getRating() << "/10.0" << endl;
}

//Ride class that stores driver, source, destination, time and whether ride has been paid
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
    virtual void select();
    void setTime(time_t time);
    void setPaid(bool paid);
    bool getPaid();
    virtual void showInfo();
    virtual void showHistory();
};

//Ride class constructor
Ride::Ride(Driver *driver, string source, string destination){
    Ride::driver = driver;
    Ride::source = source;
    Ride::destination = destination;
}

//Ride class driver getter method
Driver* Ride::getDriver() {return Ride::driver;}

//Ride class method to select current ride
void Ride::select() {driver->showInfo();}

//Ride class time setter method
void Ride::setTime(time_t time) {Ride::time = time;}

//Ride class paid setter method
void Ride::setPaid(bool paid) {Ride::paid = paid;}

//Ride class paid getter method
bool Ride::getPaid() {return Ride::paid;}

//Ride class method that prints out ride's info
void Ride::showInfo(){
    cout << setw(15) << driver->getName() << fixed << setprecision(1) << setw(8) << driver->getRating() << "$" << driver->getPrice() << endl;
}

//Ride clcass method that prints out ride's history
void Ride::showHistory(){
    cout << setw(15) << driver->getName() << setw(10) << source << setw(14) << destination << "$" << fixed << setprecision(2) << setw(8) << driver->getPrice() << setw(10) << (paid?"Paid":"Not Paid") << put_time(localtime(&time), "%Y/%m/%d %T") << endl;
}

//Carpool class that inherits from Ride class that stores number of other passengers
class Carpool : public Ride{
private:
    int passengers;
public:
    Carpool(Driver* driver, string source, string destination, int passengers);
    void select();
    void showInfo();
    void showHistory();
};

//Carpool class constructor
Carpool::Carpool(Driver* driver, string source, string destination, int passengers){
    Carpool::driver = driver;
    Carpool::source = source;
    Carpool::destination = destination;
    Carpool::passengers = passengers;
}

//Overridden Carpool class method to select current ride
void Carpool::select(){
    driver->showInfo();
    cout << "Other Passengers: " << passengers << endl;
}

//Overridden Carpool Class method that print ride's info
void Carpool::showInfo(){
    cout << driver->getName() << " " <<  setw(14-driver->getName().length()) << "(CP)" << fixed << setprecision(1) << setw(8) << driver->getRating() << "$" << driver->getPrice() << endl;
}

//Overridden Carpool Class method that prints out ride's history
void Carpool::showHistory(){
    cout << driver->getName() << " " << setw(14-driver->getName().length()) << "(CP)" << setw(10) << source << setw(14) << destination << "$" << fixed << setprecision(2) << setw(8) << driver->getPrice() << setw(10) << (paid?"Paid":"Not Paid") << put_time(localtime(&time), "%Y/%m/%d %T") << endl;
}

//Profile class that stores user's name, balance, and rides
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

//Profile class name setter method
void Profile::setName(string name) {Profile::name = name;}

//Profile class name getter method
string Profile::getName() {return Profile::name;}

//Profile class balance setter method
void Profile::setBalance(double balance) {Profile::balance = balance;}

//Profile class balance getter method
double Profile::getBalance() {return Profile::balance;}

//Profile class rides getter method
vector<Ride*> Profile::getRides() {return Profile::rides;}

//Profile class method to add ride
void Profile::addRide(Ride *ride){
    ride->setTime(time(NULL));
    ride->setPaid(false);
    Profile::rides.insert(Profile::rides.begin(), ride);
}

//Profile class method to pay ride
void Profile::payRide(int idx){
    Profile::balance -= rides[idx]->getDriver()->getPrice();
    rides[idx]->setPaid(true);
}

//Abstract Screen class that has pure virtual function to show screen
class Screen{
public:
    virtual bool showScreen() = 0;
};

//MenuScreen class that inherits from Screen class
class MenuScreen : public Screen{
public:
    bool showScreen();
};

//ProfileScreen class that inherits from Screen class
class ProfileScreen : public Screen{
public:
    bool showScreen();
};

//RideScreen class that inherits from Screen class
class RideScreen : public Screen{
public:
    bool showScreen();
};

//Array of pointers to Screen subclass objects
Screen *arr[3] = {new MenuScreen, new ProfileScreen, new RideScreen};
//Screen pointer that points to current screen
Screen **currentScreen = arr;
//Array of car structs
Car carList[5] = {{"Toyota Corolla", "QBXNB9", 5}, {"Honda Civic", "O5UXPV", 4}, {"Chevrolet Equinox", "AWST5W", 5}, {"Ford F-150", "PBL2SH", 5}, {"Nissan Rogue", "I2OIJ0", 4}};
//Array of names
string nameList[20] = {"James", "John", "Robert", "Michael", "William", "David", "Richard", "Joseph", "Thomas", "Charles", "Mary", "Patricia", "Irene", "Jennifer", "Linda", "Elizabeth", "Barbara", "Susan", "Jessica", "Sarah"};
//Array of Driver objects
Driver driverList[10];
//Pointer array of Ride/Carpool objects
Ride *rides[5];

//variables to store user input
string strInput;
int intInput;
double doubleInput;

//function that checks if user's input is valid integer
bool parseInt(){
    try{
        intInput = stoi(strInput);
        return true;
    }catch(exception e){
        return false;
    }
}

//function that checks if user's input is valid double
bool parseDouble(){
    try{
        doubleInput = stod(strInput);
        return true;
    }catch (exception e){
        return false;
    }
};

//MenuScreen class method to print out screen
bool MenuScreen::showScreen(){
    cout << "----------MENU----------" << endl;
    cout << "0->Exit" << endl;
    cout << "1->Profile" << endl;
    cout << "2->Reserve Ride" << endl;
    cout << "Enter a choice: ";
    getline(cin, strInput);
    while (!parseInt()){
        cout << "Invalid Command" << endl;
        cout << "Enter a choice: ";
        getline(cin, strInput);
    }
    if (intInput==0) return false;
    else if (intInput==1) currentScreen = arr+1;
    else {
        currentScreen = arr+2;
        string source, destination;
        cout << "Enter the source of the ride: ";
        getline(cin, source);
        cout << "Enter the destination of the ride: ";
        getline(cin, destination);
        random_shuffle(driverList, driverList+10);
        for (int i=0; i<5; i++) {
            if (!(rand()%5)) rides[i] = new Carpool(&driverList[i], source, destination, rand()%driverList[i].getCar().seats);
            else rides[i] = new Ride(&driverList[i], source, destination);
        }
    }
    return true;
}

//ProfileScreen class method to print out screen
bool ProfileScreen::showScreen(){
    cout << "----------PROFILE----------" << endl;
    cout << "Name: " << profile.getName() << endl;
    cout << "Balance: $" << fixed << setprecision(2) << profile.getBalance() << endl;
    cout << "Ride History: " << endl;
    cout << "   " << setw(15) << "NAME" << setw(10) << "SOURCE" << setw(14) << "DESTINATION" << setw(9) << "PRICE" << setw(10) << "STATUS" << "DATE" << endl;
    vector<Ride*> rideHistory = profile.getRides();
    for (int i=0; i<rideHistory.size(); i++){
        cout << (i+1) << ". ";
        rideHistory[i]->showHistory();
    }
    while (true){
        cout << "Return to main menu(0) or pay for ride(ride #) or add money(-1)? ";
        getline(cin, strInput);
        int sz = rideHistory.size();
        if (!parseInt()||intInput<-1||intInput>sz) {
            cout << "Invalid Command" << endl;
        }else if (intInput>0&&rideHistory[intInput-1]->getPaid()) {
            cout << "Already paid for this ride" << endl;
        }else if (intInput>0&&rideHistory[intInput-1]->getDriver()->getPrice()>profile.getBalance()){
            cout << "Insufficient Funds" << endl;
        }else break;
    }
    if (intInput==-1){
        while (true){
            cout << "Enter an amount: ";
            getline(cin, strInput);
            if (!parseDouble()||doubleInput<0) {
                cout << "Invalid Amount" << endl;
            }else break;
        }
        profile.setBalance(profile.getBalance()+doubleInput);
    }else if (intInput==0){
        currentScreen = arr;
    }else{
        profile.payRide(intInput-1);
        while (true){
            cout << "On a scale of 1 to 10, how did you enjoy this ride? ";
            getline(cin, strInput);
            if (!parseDouble()||doubleInput<1||doubleInput>10){
                cout << "Invalid rating" << endl;
            }else break;
        }
        rideHistory[intInput-1]->getDriver()->addRating(doubleInput);
    }
    return true;
}

//RideScreen class method to print out screen
bool RideScreen::showScreen(){
    cout << "----------RIDES----------" << endl;
    cout << "#  " << setw(15) << "NAME" << "RATING" << "  PRICE" << endl;
    for (int i=0; i<5; i++){
        cout << (i+1) << ". ";
        rides[i]->showInfo();
    }
    while (true){
        cout << "Return to main menu(0) or view a ride(ride #)? ";
        getline(cin, strInput);
        if (!parseInt()||intInput<0||intInput>5){
            cout << "Invalid Command" << endl;
        }else break;
    }
    if (intInput==0){
        currentScreen = arr;
    }else{
        int idx = --intInput;
        rides[idx]->select();
        while (true){
            cout << "Choose this ride(0) or go back(1)? ";
            getline(cin, strInput);
            if (!parseInt()||intInput<0||intInput>1){
                cout << "Invalid Command" << endl;
            }else break;
        }
        if (intInput==0){
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

//initializes user's profile and randomly creates Driver objects with random ratings
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
        driverList[i] = Driver(nameList[idx], carList[rand()%5], (double) (rand()%10)+10);
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
