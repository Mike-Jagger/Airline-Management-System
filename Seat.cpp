#include <iostream>
#include "Seat.h"

using namespace std;

// DefaultcConstructor
Seat::Seat(): row("-1"), col(-1) {};

Seat::Seat(string row_n, int col_n) {
    row = row_n;
    col = col_n;
}

// Copy constructor
Seat::Seat(const Seat& src) {
    row = src.row;
    col = src.col;
}

// Copy by assignment
Seat& Seat::operator = (Seat& rhs) {
    if(this != &rhs) {
        row = rhs.row;
        col = rhs.col;
    }
    return *this;
}

// Getters
string Seat::get_row() const { return row; }
int Seat::get_col() const { return col; }

// Setters
void Seat::set_row(string value) { row = value; }
void Seat::set_col(int value) { col = value; }