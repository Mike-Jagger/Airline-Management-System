#ifndef PASSENGER_H
#define PASSENGER_H
#include <string>

#include "Seat.h"

using namespace std;

class Passenger {
public:
    // Constructors
    Passenger();
    Passenger(string firstname, string lastname, string phone_num, string row_n, int col_n, string Id);

    // Copy constructors
    Passenger(const Passenger& src);
    Passenger& operator = (Passenger& rhs);

    // Getters
    string get_fname() const;
    string get_lname() const;
    string get_phone() const;
    string get_id() const;
    Seat get_seat() const;

    // Setters
    void set_fname(string value);
    void set_lname(string value);
    void set_phone(string value);
    void set_id(int value);
    void set_seat(string i, int j);


private:
    string fname;
    string lname;
    string phone;
    string id;
    Seat seat;
};


#endif /* Passenger.h */