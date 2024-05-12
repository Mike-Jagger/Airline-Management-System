#ifndef SEAT_H
#define SEAT_H

#include <string>

using namespace std;

class Seat {
public:
    // Constructors
    Seat();
    Seat(string row_n, int col_n);

    // Copy constructors
    Seat(const Seat& src);
    Seat& operator = (Seat& rhs);

    // Getters
    string get_row() const;
    int get_col() const;

    // Setters
    void set_row(string value);
    void set_col(int value);

private:
    string row;
    int col;
};


#endif /* Seat.h */