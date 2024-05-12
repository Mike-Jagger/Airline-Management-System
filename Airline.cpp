#include <iostream>
#include <string>

#include "Airline.h"
#include "Flight.h"

using namespace std;

// Constructors
Airline::Airline(): name(""), flight(0) {}
Airline::Airline(string name, Flight* flight): name(name), flight(flight) {}

// Destructor
Airline::~Airline() {
    name = "";
    delete flight;
}

// Getters
string Airline::get_name() const { return name; }
const Flight* Airline::get_flight() const { return flight; }
Flight* Airline::modify_flight() const {return flight;}

// Setters
void Airline::set_name(string value) { name = value; }
void Airline::set_flight(Flight* flight_d) { flight = flight_d; };
