#ifndef FLIGHT_H
#define FLIGHT_H

#include "Passenger.h"

using namespace std;

struct Node {
    Passenger passenger;
    Node *next;
};

class Flight {
public:
    // Constructors
    Flight();
    Flight(int rows, int cols);

    // Destructor
    ~Flight();

    // Getters
    int get_rows() const;
    int get_cols() const;
    const Node* get_head() const;

    // Setters
    void set_rows(int n_rows);
    void set_cols(int n_cols);

    void add_passenger(string fname, string lname, string phone, string row, int col, string id);
    void remove_passenger(string id);

private:
    int rows;
    int cols;
    Node* headM;
    void destroy();
};


#endif /* Flight.h */