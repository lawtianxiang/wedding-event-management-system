#include "utils.h"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void displayIntroduction() {
    cout << "***********************************************************\n";
    cout << "*                                                         *\n";
    cout << "*     Welcome to the Wedding Event Management System      *\n";
    cout << "*                                                         *\n";
    cout << "***********************************************************\n";
}

void displayMenu() {
   
    cout << "======================== MENU ========================\n";
    cout << "1. Event Registration \n";
    cout << "2. Payment \n";
    cout << "3. Staff Management\n";
    cout << "4. Generate Reports\n";
    cout << "5. Guest List Management\n";
    cout << "6. Exit\n";
    cout << "======================================================\n";
}

void displayEndingMessage() {
    cout << "\nThank you for using the Event Management System. Goodbye!\n";
}

void pauseSystem() {
    cout << "\nPress Enter to continue...\n";
    cin.get();
}


Event* findEventById(vector<Event>& events, int id) {
    for (auto& event : events) {
        if (event.eventId == id) {
            return &event;
        }
    }
    return nullptr;
}
