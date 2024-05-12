#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>

#include "main.h"
#include "Airline.h"
#include "Seat.h"
#include "Passenger.h"
#include "Flight.h"
#include <iomanip>

using namespace std;

/* Helper functions */
std::string replaceSpacesWithHyphens(const std::string& phoneNumber) {
    std::string modifiedNumber = phoneNumber;

    // Find and replace spaces with hyphens
    size_t found = modifiedNumber.find(' ');
    while (found != std::string::npos) {
        modifiedNumber[found] = '-';
        found = modifiedNumber.find(' ', found + 1);
    }

    return modifiedNumber;
}

void removeTrailingSpaces(std::string& str) {
    size_t endpos = str.find_last_not_of(" \t\r\n"); // Find the last non-space character
    if (endpos != std::string::npos) {
        str = str.substr(0, endpos + 1); // Remove trailing spaces
    } else {
        str.clear(); // If the string is all spaces, clear the entire string
    }
}

int convertCharArrayToInt(string charArray) {
    int result = 0;
    int sign = 1;
    int i = 0;
    string zero = "0";
    string nine = "9";

    // Convert each character to its numeric value and build the integer
    while ( i < (int) charArray.size()) {
        string char_;
        char_.resize(1);

        char_[0] = charArray[i];

        if (char_ >= zero && char_ <= nine) {
            result = result * 10 + (charArray[i] - '0');
        }
        i++;
    }

    return result * sign;
}

/* Display functions*/

void display_header() {
    cout << "Version 1.0" << endl <<
            "Term Project - Flight Management Program in C++" << endl <<
            "Produced by: Mendjemo Ngangom Gerard Ledoux" << endl <<
            "\n<<< Press Return to Continue >>>>";
    cin.clear();
    cin.get();
    cout << "<<< Press Return to Continue >>>>";
    cin.get();
}

void display_info(Airline* airline) {
        const Flight* flight = airline->get_flight();

        cout << endl << left << setw(20) << "First Name"
                << setw(20) << "Last Name"
                << setw(20) << "Phone"
                << setw(6) << "Row" 
                << setw(6) << "Seat" 
                << setw(5) << "ID" << endl;

        for(const Node* p = flight->get_head(); p != 0; p = p->next) {
            Seat seat = p->passenger.get_seat();
            string seat_row = seat.get_row();

            char seat_col = 'A' + (int) seat.get_col();

            cout << "-------------------------------------------------------------------------------" << endl;

            cout << setfill(' ') << left << setw(20) << p->passenger.get_fname() << 
                setw(20)<< (p->passenger.get_lname()) << 
                setw(20) << (p->passenger.get_phone()) <<  
                setw(6) << seat_row <<
                setw(6) << seat_col <<
                setw(5)<< (p->passenger.get_id()) << endl;
        }

        
}

void display_flight(Airline* airline) {
    const Flight* flight = airline->get_flight();

    cout << "      A   B   C   D   E   F" << endl;
    for(int i_ = 0; i_ < flight->get_rows(); i_++) {
        cout << "    +---+---+---+---+---+---+" << endl;
        string i = to_string(i_);
        cout << left << setw(2) << i;
        cout << right << setw(3) << "|";

        int j, flag;
        for(j = 0; j <= flight->get_cols(); j++) {
            flag = 0; // Seat taken

            // Parse through passengers list to see if anyone occupies the seat
            for(const Node* p = flight->get_head(); p != 0; p = p->next) {
                Seat seat = p->passenger.get_seat();
                string seat_row = seat.get_row();
                int seat_col = seat.get_col();

                // Check if the seat is occupied
                int seat_ = convertCharArrayToInt(seat_row); // Convert seat row to int
                //cout << seat_col << " " << j <<";";
                if(i_ == seat_ && j == seat_col) {
                    flag = 1;
                }
            }
            if(flag) {
                cout << " X |";
            }
            else {
                if(j < 5){
                    cout << "   |";
                }  
            }
            
        }
        if(!flag) {
            cout << "   |";
        }
        
        cout << endl;
    }
    cout << "    +---+---+---+---+---+---+" << endl;
}

/* File manipulation functions */

void populate_flight_from_file(const char *filename, Airline* airline) {
    Flight* new_flight = new Flight;
    assert(new_flight != 0);

    ifstream in(filename);

    // Gather info about the ailine
    string airline_name;

    // Gather info about the flight seating
    int rows, cols;

    // Scan first line of file
    in >> airline_name >> rows >> cols;

    // Set airline's name and flight details
    airline->set_name(airline_name);
    new_flight->set_cols(cols);
    new_flight->set_rows(rows);

    // Gather passenger info
    string passenger_info;
    string fname, lname, phone, seat_num, row, id;
    int col;

    while(!in.eof()) {
        getline(in, passenger_info, '\n');

        if(passenger_info != "") {
            //Get first name (First 20 characters)
            fname.resize(20);
            for(int i = 0; i < 20; i++) {
                fname += passenger_info[i];
            }
            fname = fname.substr(20, 40);

            //Get last name (next 20 characters)
            lname.resize(20);
            for(int i = 20; i < 40; i++) {
                lname += passenger_info[i];
            }
            lname = lname.substr(20, 40);

            //Get phone number (next 20 characters)
            phone.resize(20);
            for(int i = 40; i < 60; i++) {
                phone += passenger_info[i];
            }
            phone = phone.substr(20, 40);

            //Get seat number (next 4 characters)
            seat_num.resize(4);
            for(int i = 60; i < 64; i++) {
                seat_num += passenger_info[i];
            }
            removeTrailingSpaces(seat_num);

            // Resize seat num to give exact size
            if((int) seat_num.size() - 4 == 2) {
                seat_num = seat_num.substr(4, 5);
            }
            else if((int) seat_num.size() - 4 == 3) {
                seat_num = seat_num.substr(4, 6);
            }
            
            // Extract row and  column parts
            col = seat_num[seat_num.size() - 1] - 'A';
            row.resize(seat_num.size() - 1);
            for(int i = 0; i < (int) row.size(); i++) {
                row[i] = seat_num[i];
            }
            
            //Get ID (next 5 characters)
            id.resize(5);
            for(int i = 64; i < 69; i++) {
                id += passenger_info[i];
            }
            id = id.substr(5, 9);

            // Add a flight to the list
            new_flight->add_passenger(fname, lname, phone, row, col, id);
        }
    }

    // Set airline's flight to new_flight
    airline->set_flight(new_flight);

    in.close();
}

void populate_file_from_flight(const char *filename, Airline* airline) {
    const Flight* flight = airline->get_flight();

    ofstream out(filename);

    // Add flight details
    out << left << setw(9) << airline->get_name() 
        << setw(6) << flight->get_rows()
        << setw(5) << flight->get_cols();

    // Add passenger details
    for(const Node* p = flight->get_head(); p != 0; p = p->next) {
            Seat seat = p->passenger.get_seat();
            string seat_row = seat.get_row();

            char seat_col = 'A' + (int) seat.get_col();
            seat_row += seat_col;
            out << endl;
            out << setfill(' ') << left << setw(20) << p->passenger.get_fname() << 
                setw(20)<< (p->passenger.get_lname()) << 
                setw(20) << (p->passenger.get_phone()) <<  
                setw(4) << seat_row <<
                setw(5)<< (p->passenger.get_id());
        }

    out.close();
}

/* Flight modification functions */

void add_new_passenger(Airline* airline, string fname, string lname, string phone, string row, int col, string id) {
    Flight* flight = airline->modify_flight();
    flight->add_passenger(fname, lname, phone, row, col, id);
}

void remove_passenger(Airline* airline, string id) {
    Flight* flight = airline->modify_flight();
    flight->remove_passenger(id);
}

int main() {
    display_header();

    Airline* new_airline = new Airline;
    assert(new_airline != 0);

    populate_flight_from_file("flight_info.txt", new_airline);


    int choice, c = 1;

    while(c) {
        choice = menu();

        // Phone number variables
        string first, second, third;
        string hyph("-");
        
        string empty; //to clear input buffer
        string fname, lname, phone, row, id , id_removed;
        int col;
        char seat;

        switch (choice)
        {
            case 1:
                display_flight(new_airline);
                break;

            case 2:
                display_info(new_airline);
                break;

            case 3:
                getline(cin, empty, '\n');
                cin.clear();

                cout << "\nPlease enter the passenger id: ";
                getline(cin, id, '\n');
                cin.clear();

                cout << "Please enter the passenger first name: ";
                getline(cin, fname, '\n');

                cin.clear();
                cout << "Please enter the passenger last name: ";
                getline(cin, lname, '\n');
                
                cout << "Please enter the passenger phone number: ";
                getline(cin, phone, '\n');
                
                cout << "\nPlease enter the passenger row: ";
                cin >> row;
                removeTrailingSpaces(row);
                
                cout << "Please enter the passenger seat: ";
                cin >> seat;
                col = seat - 'A';

                phone = replaceSpacesWithHyphens(phone);

                add_new_passenger(new_airline, fname, lname, phone, row, col, id);
                break;
            
            case 4:
                cout << "Please enter the id of the passenger that needs to be removed: ";
                cin >> id_removed;
                remove_passenger(new_airline, id_removed);
                break;

            case 5:
                //populate_file_from_flight("test.txt", new_airline);
                populate_file_from_flight("flight_info.txt", new_airline);
                break;

            case 6:
                cout << "\nProgram terminated.";
                c = 0;
                break;
            
            default:
                cout << "Wrong Entry";
                break;
        }
    }

    return 0;
}

int menu() {
    int choice, c = 1;
    
    // Display menu
    cout << "\nPlease select one of the following options" << endl <<
            "1. Display Flight Seat Map." << endl <<
            "2. Display Passengers Information" << endl <<
            "3. Add a New Passenger" << endl <<
            "4. remove an Existing Passenger" << endl <<
            "5. Save Data" << endl <<
            "6. Quit" << endl;

    cout << "\nEnter your choice: (1, 2, 3, 4, 5 or 6) ";
    cin >> choice;

    // Error handling of choice input
    while(c) {
        if((choice >= 1) && (choice <= 6)) {
            c = 0;
        }
        else {
            cout << "\nEnter your choice: (1, 2, 3, 4, 5 or 6) ";
            cin >> choice;
        }
    }

    return choice;
}