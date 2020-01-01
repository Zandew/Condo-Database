#pragma once
#include <iostream>

using namespace std;

class Car{
	private:
		string license, model;
		int seats;
	public:
		Car(string license, string model, int seats);
		~Car();
};
