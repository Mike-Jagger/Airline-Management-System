#include <iostream>
#include <assert.h>
#include <string>

#include "Passenger.h"
#include "Seat.h"

using namespace std;

// DefaultcConstructor
Passenger::Passenger(): fname(""), lname(""), phone(""), id("00000") {};

Passenger::Passenger(string firstname, string lastname, string phone_num, string row_n, int col_n, string Id) {
    fname = firstname;
    lname = lastname;
    phone = phone_num;
    id = Id;
    Seat new_seat(row_n, col_n);
    seat = new_seat;
}

// Copy constructor
Passenger::Passenger(const Passenger& src) {
    fname = src.fname;
    lname = src.lname;
    phone = src.phone;
    id = src.id;
    Seat new_seat = src.seat;
    seat = new_seat;
}

// Copy by assignment
Passenger& Passenger::operator = (Passenger& rhs) {
    if (this != &rhs) {
        fname = rhs.fname;
        lname = rhs.lname;
        phone = rhs.phone;
        id = rhs.id;
        seat = rhs.seat;
    }
    return *this;
}

// Getters
string Passenger::get_fname() const { return fname; }
string Passenger::get_lname() const { return lname; }
string Passenger::get_phone() const { return phone; }
string Passenger::get_id() const { return id; }
Seat Passenger::get_seat() const { return seat; }

// Setters
void Passenger::set_fname(string value) {fname = value; }
void Passenger::set_lname(string value) { lname = value; }
void Passenger::set_phone(string value) { phone = value; }
void Passenger::set_id(int value) { id = value; }
void Passenger::set_seat(string i, int j) { 
    Seat new_seat(i, j);
    seat = new_seat;
}