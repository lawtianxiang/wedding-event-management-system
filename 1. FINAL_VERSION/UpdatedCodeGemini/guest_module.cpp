#include "guest_module.h"
#include "utils.h"
#include "validation.h"
#include "event_module.h"
#include <iostream>
#include <vector>

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
        case 1: addGuest(*event); break;
        case 2: viewGuests(*event); break;
        case 3: removeGuest(*event); break;
        case 4: break;
        }
        if (choice != 4) pauseSystem();
    } while (choice != 4);
}

// add a guest to the event's guest list
void addGuest(Event& event) {
    string guestName = getValidatedName("\nEnter guest's full name to add: ");
    string phoneNumber = getValidatedPhoneNumber("\nEnter guest's phone number: ");

    event.guestList.push_back(guestName);
    cout << "'" << guestName << "' has been added to the guest list.\n";
}

// view all guests in the event's guest list
void viewGuests(const Event& event) {
    cout << "\n--- Guest List for Event ID: " << event.eventId << " ---\n";
    if (event.guestList.empty()) {
        cout << "The guest list is currently empty.\n";
        return;
    }
    int count = 1;
    for (const auto& guest : event.guestList) {
        cout << count++ << ". " << guest << endl;
    }
}

// remove a guest from the event's guest list
void removeGuest(Event& event) {
    viewGuests(event);
    string guestName = getValidatedName("\nEnter the full name of the guest to remove: ");

    for (auto it = event.guestList.begin(); it != event.guestList.end(); ++it) {
        if (*it == guestName) {
            event.guestList.erase(it);
            cout << "'" << guestName << "' has been removed from the guest list.\n";
            return;
        }
    }
    cout << "Guest not found in the list.\n";
}
