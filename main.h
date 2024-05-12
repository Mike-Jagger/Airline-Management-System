#ifndef MAIN_H
#define MAIN_H
#include "Airline.h"

/* Helper functions */
int convertCharArrayToInt(string charArray);
void removeTrailingSpaces(std::string& str);

/* Display functions */

void display_header();
void display_info(Airline* airline);
void display_flight(Airline* airline);


/* File manipulation functions*/
void populate_flight_from_file(const char *filename, Airline* airline);
void populate_file_from_flight(const char *filename, Airline* airline);

/* Flight modification functions*/
void add_new_passenger(Airline* airline, string fname, string lname, string phone, string row, int col, string id);
void remove_passenger(Airline* airline, string id);

/* Menu */
int menu();

#endif /* main.h */