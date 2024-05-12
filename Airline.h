#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include "Flight.h"

using namespace std;

// This class assumes there is only one flight
class Airline {
public:
    // Constructors
    Airline();
    Airline(string name, Flight* flight);

    // Destructor
    ~Airline();

    // Getters
    string get_name() const;
    const Flight* get_flight() const;
    Flight* modify_flight() const;

    // Setters
    void set_name(string value);
    void set_flight(Flight* flight_d);

private:
    string name;
    Flight* flight;
};

#endif /* Airline.h */