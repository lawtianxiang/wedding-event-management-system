#include "guest_module.h"
#include "utils.h"
#include "validation.h"
#include "event_module.h"
#include "file_handler.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

// main menu for guest list management
void handleGuestList(vector<Event>& events) {
    viewAllEvents(events);
    int id = getValidatedInteger("\nEnter Event ID to manage the guest list: ");
    Event* event = findEventById(events, id);
    if (event == nullptr) {
        cout << "Event ID not found.\n";
        return;
    }
    int choice;
    do {
        cout << "\n--- Guest List Management for Event ID: " << id << " ---\n";
        cout << "1. Add Guest\n";
        cout << "2. View Guest List\n";
        cout << "3. Remove Guest\n";
        cout << "4. Back to Main Menu\n";
        choice = getValidatedChoice(1, 4);
        switch (choice) {
        case 1: addGuest(*event, events); break;
        case 2: viewGuests(*event); break;
        case 3: removeGuest(*event); break;
        case 4: break;
        }
        if (choice != 4) pauseSystem();
    } while (choice != 4);
}

// add a guest to the event's guest list
void addGuest(Event& event, vector<Event>& events) {
    Client newGuest;
    newGuest.name = getValidatedName("\nEnter guest's full name to add: ");
    newGuest.contactNumber = getValidatedPhoneNumber("Enter guest's phone number: ");
    newGuest.rating = getValidatedDouble("Enter guest's rating (0.0 - 5.0): ");
    newGuest.feedback = getNonEmptyString("Enter guest's feedback: ");

    // Sanitize feedback
    replace(newGuest.feedback.begin(), newGuest.feedback.end(), '|', '/');
    replace(newGuest.feedback.begin(), newGuest.feedback.end(), ',', ';');

    event.guestList.push_back(newGuest);
    saveDataToFile(events);

    cout << "'" << newGuest.name << "' has been added as a guest entry for Event ID " << event.eventId << ".\n";
}

// view all guests in the event's guest list
void viewGuests(const Event& event) {
    cout << "\n----------------------------------------------------\n";
    cout << "Guest List for Event ID: " << event.eventId << "\n";
    cout << "Client: " << event.client.name << "\n";
    cout << "----------------------------------------------------\n\n";

    if (event.guestList.empty()) {
        cout << "No guests have been added to this event.\n";
        return;
    }

    cout << left << setw(5) << "No."
        << setw(25) << "Guest Name"
        << setw(15) << "Contact"
        << setw(10) << "Rating"
        << "Feedback\n";
    cout << string(80, '-') << "\n";

    int count = 1;
    for (const auto& guest : event.guestList) {
        cout << left << setw(5) << count++
            << setw(25) << guest.name
            << setw(15) << guest.contactNumber
            << setw(10) << fixed << setprecision(1) << guest.rating
            << guest.feedback << "\n";
    }
}



// remove a guest from the event's guest list
void removeGuest(Event& event) {
    viewGuests(event);
    string guestName = getValidatedName("\nEnter the full name of the guest to remove: ");

    for (auto it = event.guestList.begin(); it != event.guestList.end(); ++it) {
        if (it->name == guestName) {
            event.guestList.erase(it);
            cout << "'" << guestName << "' has been removed from the guest list.\n";
            return;
        }
    }
    cout << "Guest not found in the list.\n";
}