#include <iostream>
#include <string>
#include <assert.h>

#include "Flight.h"
#include "Passenger.h"
#include "main.h"


using namespace std;


// Default constructor
Flight::Flight(): rows(0), cols(0), headM(0) {}

// Constructor
Flight::Flight(int rows, int cols): rows(rows), cols(cols) {
    Node* new_pass = new Node;
    assert(new_pass != 0);
    new_pass->next = headM;
    headM = 0;
}

// Destructor
Flight::~Flight(){
    destroy();
}

// Getters
int Flight::get_rows() const {return rows;}
int Flight::get_cols() const {return cols;}
const Node* Flight::get_head() const {return headM;}

// Setters
void Flight::set_rows(int n_rows) { rows = n_rows; }
void Flight::set_cols(int n_cols) { cols = n_cols; }

void Flight::destroy() {
    rows = 0;
    cols = 0;

    Node* next = headM;
    Node* prev;

    while(next != 0) {
        prev = next;
        next = next->next;
        delete prev;
    }
    headM = 0;
}

void Flight::add_passenger(string fname, string lname, string phone, string row, int col, string id) {
    Passenger new_passenger(fname, lname, phone, row, col, id);
    Node* new_pass = new Node;
    assert(new_pass != 0);

    new_pass->passenger = new_passenger;

    if(headM == 0) {
        new_pass->next = headM;
        headM = new_pass;
    }
    else if(convertCharArrayToInt(new_passenger.get_id()) < convertCharArrayToInt(headM->passenger.get_id())) {
        new_pass->next = headM;
        headM = new_pass;
    }
    else {
        Node *before = headM;
        Node *after = headM->next;

        // Move to next seat if greater than the previous
        while(after != 0 && (convertCharArrayToInt(new_passenger.get_id()) > convertCharArrayToInt(after->passenger.get_id()))) {
            before = after;
            after = after->next;
        }

        new_pass->next = after;
        before->next = new_pass;
    }
}

void Flight::remove_passenger(string id) {
    if (headM == 0) {
        return;
    }

    Node *removed_pass = 0; // Passenger to be removed

    // Check if head node is the passenger to be removed
    if(id == headM->passenger.get_id()) {
        removed_pass = headM;
        headM = headM->next;
    }
    // if not head node, check other passengers
    else {
        Node *before = headM;
        Node *maybe_removed = headM->next;

        // Move to next passenger if ids don't match
        while(maybe_removed != 0 && id != maybe_removed->passenger.get_id()) {
            before = maybe_removed;
            maybe_removed = maybe_removed->next;
        }

        // If ids match, select that passenger as passenger to be removed
        if(maybe_removed != 0 && maybe_removed->passenger.get_id() == id) {
            removed_pass = maybe_removed;
            before->next = maybe_removed->next;
        }
    }

    delete removed_pass; // Delete passenger details

}

// Potential addition

// Check if the next seat is the same as the new seat
        /* if((new_passenger.get_seat().get_row() == after->passenger.get_seat().get_row()) && (new_passenger.get_seat().get_col() == after->passenger.get_seat().get_col())) {
            string ch;
            int c = 1;


            cout << "WARNING: You are about to change the occupant of this seat";

            // Confirm change
            while(c) {
                cout<<"\nContinue (Y/N): ";
                cin >> ch;
                
                // Change next node to new node
                if(ch == "y" or ch == "Y") {
                    after->passenger = new_passenger;
                }
                // Leave unchanged
                else if(ch == "n" or ch == "N") {
                    c = 0;
                }
                else {
                    cin >> ch;
                }
            }

        }
        // Check if the previous seat is the same as the new seat
        else if((new_passenger.get_seat().get_row() == before->passenger.get_seat().get_row()) && (new_passenger.get_seat().get_col() == before->passenger.get_seat().get_col())) {
            string ch;
            int c = 1;

            cout << "WARNING: You are about to change the occupant of this seat";

            // Confirm change
            while(c) {
                cout<<"\nContinue (Y/N): ";
                cin >> ch;

                // Change next node to new node
                if(ch == "y" or ch == "Y") {
                    before->passenger = new_passenger;
                }
                // Leave unchanged
                else if(ch == "n" or ch == "N") {
                    c = 0;
                }
                else {
                    cin >> ch;
                }

            }
        } 

        // If the new seat is not equal the previous and current one
        else {
            new_pass->next = after;
            before->next = new_pass;
        } */