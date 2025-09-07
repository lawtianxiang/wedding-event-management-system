#include "event_module.h"
#include "utils.h"
#include "validation.h"
#include "file_handler.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// main menu for event registration management
void handleEventRegistration(vector<Event>& events) {
    int choice;
	do {
        cout << "\n--- Event Registration Management ---\n";
        cout << "1. Register New Event\n";
        cout << "2. View All Events\n";
        cout << "3. View Package Comparison\n";
        cout << "4. Cancel an Event\n";
        cout << "5. Add On\n";
        cout << "6. Back to Main Menu\n";
		choice = getValidatedChoice(1, 6);
        switch (choice) {
		case 1: registerNewEvent(events); break;
		case 2: viewAllEvents(events); break;
		case 3: displayPackageComparison(); break;
		case 4: cancelEvent(events); break;
		case 5: addOn(events); break;
		case 6: break;
        }
        if (choice != 6) pauseSystem();
    } while (choice != 6);
}

// register new event by entering details
void registerNewEvent(vector<Event>& events) {
    Event newEvent;
    newEvent.eventId = events.empty() ? 101 : events.back().eventId + 1;
    cout << "\n--- Registering a New Wedding Event (ID: " << newEvent.eventId << ") ---\n";

    newEvent.client.name = getValidatedName("Enter the Couples' Names: ");
	newEvent.client.contactNumber = getValidatedPhoneNumber("Enter a Contact Number: ");
	newEvent.eventDate = getValidatedDate("Enter Event Date (YYYY-MM-DD): ");
	newEvent.eventTime = getValidatedTime("Enter Event Time (HH:MM): ");

    int guests = 0;
    while (guests <= 0) {
		guests = getValidatedInteger("Enter Estimated Guest Count: ");
        if (guests <= 0) cout << "Guest count must be a positive number.\n";
    }
    newEvent.estimatedGuests = guests;
	newEvent.packageChoice = getNonEmptyString("Choose a Package (e.g.Gold, Silver, Bronze): ");
    newEvent.paymentDetails.invoiceId = newEvent.eventId + 5000;
	newEvent.paymentDetails.amount = getValidatedDouble("Enter Package Price: ");
    newEvent.paymentDetails.status = "Pending";
	events.push_back(newEvent);
    saveDataToFile(events);
    cout << "\n(Success) Event for " << newEvent.client.name << " registered successfully!\n";
}

// display all events in a formatted table
void viewAllEvents(const vector<Event>& events) {
    cout << "\n--- All Registered Events ---\n";
    if (events.empty()) {
        cout << "No events registered yet.\n";
        return;
    }
    cout << left << setw(10) << "Event ID" << setw(25) << "Client Name" << setw(15) << "Date" << setw(10) << "Guests" << setw(15) << "Package" << setw(15) << "Pay Status" << endl;
    cout << string(90, '-') << endl;
    for (const auto& event : events) {
        cout << left << setw(10) << event.eventId << setw(25) << event.client.name << setw(15) << event.eventDate << setw(10) << event.estimatedGuests << setw(15) << event.packageChoice << setw(15) << event.paymentDetails.status << endl;
    }
}

// find event by ID to update information
void updateEventInfo(vector<Event>& events) {
    viewAllEvents(events);
    int id = getValidatedInteger("\nEnter Event ID to update: ");
    Event* eventToUpdate = findEventById(events, id);
    if (eventToUpdate == nullptr) {
        cout << "Event ID not found.\n";
        return;
    }
    cout << "\nUpdating Event ID: " << id << ". What would you like to change?\n";
    cout << "1. Estimated Guest Count\n";
    cout << "2. Package Choice\n";
    int choice = getValidatedChoice(1, 2);
    if (choice == 1) {
        int newGuests = 0;
        while (newGuests <= 0) {
            newGuests = getValidatedInteger("Enter new guest count: ");
            if (newGuests <= 0) cout << "Guest count must be a positive number.\n";
        }
        eventToUpdate->estimatedGuests = newGuests;
    }
    else {
        eventToUpdate->packageChoice = getNonEmptyString("Enter new package choice: ");
    }
    cout << "(Success) Event information updated!\n";
}

// delete event by ID
void cancelEvent(vector<Event>& events) {
    viewAllEvents(events);
    int id = getValidatedInteger("\nEnter Event ID to delete: ");
    for (auto it = events.begin(); it != events.end(); ++it) {
        if (it->eventId == id) {
            events.erase(it);
            cout << "(Success) Event ID " << id << " has been deleted.\n";
            return;
        }
    }
    cout << "Event ID not found.\n";
}

// add task to an event
void addTaskToEvent(Event& event) {
    Task newTask;
    newTask.description = getNonEmptyString("\nEnter task description: ");
    newTask.status = "Pending";
    event.tasks.push_back(newTask);
    cout << "(Success) Task added!\n";
}

//add on extra services or tasks to an existing event
void addOn(vector<Event>& events) {
    viewAllEvents(events);
    int id = getValidatedInteger("\nEnter Event ID to manage tasks: ");
    Event* event = findEventById(events, id);
    if (event == nullptr) {
        cout << "Event ID not found.\n";
        return;
    }
    system("cls");
    cout << "--- Task Management for Event ID: " << id << " ---\n";
    if (!event->tasks.empty()) {
        cout << "Current Tasks:\n";
        for (const auto& task : event->tasks) {
            cout << "- " << task.description << " [" << task.status << "]\n";
        }
    }
    else {
        cout << "No tasks assigned to this event yet.\n";
    }
    cout << "\n1. Add New Task\n";
    cout << "2. Back to Event Menu\n";
    int choice = getValidatedChoice(1, 2);
    if (choice == 1) {
        addTaskToEvent(*event);
    }
}

void displayPackageComparison() {

    const int NUM_PACKAGES = 3;
    const int NUM_FEATURES = 4;
    const string packages[NUM_PACKAGES][NUM_FEATURES] = {
        // Package Name,      Day,        Photographer,             Catering
        { "Bronze Package", "1 Day",     "Not Included",        "Standard Menu" },
        { "Silver Package", "1 Day",     "Included (All Day)",  "Deluxe Menu"   },
        { "Gold Package",   "1 Day",     "Included (All Day)",  "Premium Menu"  }
    };

    system("cls");
    cout << "--- Wedding Package Comparison ---\n\n";

    // Print the header
    cout << left << setw(20) << "Package" << setw(15) << "Venue" << setw(25) << "Photographer" << setw(20) << "Catering" << endl;
    cout << string(80, '-') << endl;

    // Loop through the 2D array to print the details
    for (int i = 0; i < NUM_PACKAGES; ++i) {
        cout << left << setw(20) << packages[i][0]
            << setw(15) << packages[i][1]
            << setw(25) << packages[i][2]
            << setw(20) << packages[i][3] << endl;
    }
}
