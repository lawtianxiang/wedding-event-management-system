#include "staff_module.h"
#include "utils.h"
#include "validation.h"
#include "event_module.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Main menu for staff management
void handleStaffManagement(vector<Event>& events) {
    viewAllEvents(events);
    int id = getValidatedInteger("\nEnter Event ID to manage staff: ");
    Event* event = findEventById(events, id);
    if (event == nullptr) {
        cout << "Event ID not found.\n";
        return;
    }
    int choice;
    do {
        cout << "\n---------------------------------------\n";
        cout << "|Managing Staff for Event ID: " << event->eventId << "     |\n";
        cout << "|Client: " << event->client.name << "                          |\n";
        cout << "|Date: " << event->eventDate << "                     |\n";
        cout << "---------------------------------------\n\n";
        cout << "--- Staff Management Menu ---\n";
        cout << "1. Add Staff\n";
        cout << "2. View Assigned Staff\n";
        cout << "3. Modify Staff Details\n";
        cout << "4. De-allocate Staff\n";
        cout << "5. Back to Main Menu\n";
        choice = getValidatedChoice(1, 5);
        switch (choice) {
         case 1: addStaffToEvent(*event); break;
         case 2: viewEventStaff(*event); break;
         case 3: modifyStaffDetails(*event); break;
         case 4: deallocateStaffFromEvent(*event); break;
         case 5: break;
        }
        if (choice != 5) pauseSystem();
    } while (choice != 5);
}

// Add a new staff member to the event
void addStaffToEvent(Event& event) {
    Staff newStaff;
    cout << "\n--- Adding New Staff ---\n";
    newStaff.staffId = getNonEmptyString("Enter Staff ID (e.g., S101): ");

    newStaff.name = getValidatedName("Enter Staff Name: ");

    string role;
    while (true) {
        role = getNonEmptyString("Enter Role (Manager, Chef, Waiter, Security, MC): ");
        if (role == "Manager" || role == "Chef" || role == "Waiter" || role == "Security" || role == "MC") {
            newStaff.role = role;
            break;
        }
        else {
            cout << "Invalid role. Please choose from the specified options.\n";
        }
    }
    newStaff.dutyPlace = getNonEmptyString("Enter Duty Place (e.g., Main Hall, Kitchen): ");
    newStaff.attendance = "Absent";
    event.assignedStaff.push_back(newStaff);
    cout << "\n(Success) Staff member added successfully!\n";
}

// View all staff assigned to the event in a formatted table
void viewEventStaff(const Event& event) {
  
    cout << "\n----------------------------------------------------\n";
    cout << "Viewing Staff for Event ID: " << event.eventId << "\n";
    cout << "Client: " << event.client.name << "\n";
    cout << "------------------------------------------------------\n\n";
    if (event.assignedStaff.empty()) {
        cout << "No staff have been assigned to this event yet.\n";
        return;
    }
    cout << left << setw(10) << "Staff ID" << setw(25) << "Name" << setw(15) << "Role" << setw(20) << "Duty Place" << setw(15) << "Attendance" << endl;
    cout << string(85, '-') << endl;
    for (const auto& staff : event.assignedStaff) {
        cout << left << setw(10) << staff.staffId << setw(25) << staff.name << setw(15) << staff.role << setw(20) << staff.dutyPlace << setw(15) << staff.attendance << endl;
    }
}

// Modify details of an assigned staff member
void modifyStaffDetails(Event& event) {
    if (event.assignedStaff.empty()) {
        cout << "No staff assigned to this event yet to modify.\n";
        return;
    }
    viewEventStaff(event);
    string staffId = getNonEmptyString("\nEnter Staff ID to modify: ");

    // Find the staff member to modify
    for (auto& staff : event.assignedStaff) {
        if (staff.staffId == staffId) {
            // Found the staff member, now show the edit menu
            system("cls");
            cout << "--- Modifying Staff Member: " << staff.name << " ---\n";
            cout << "Current Role: " << staff.role << "\n";
            cout << "Current Duty Position: " << staff.dutyPlace << "\n";
            cout << "Current Attendance: " << staff.attendance << "\n";
            cout << "-------------------------------------------\n";
            cout << "What would you like to edit?\n";
            cout << "1. Edit Attendance\n";
            cout << "2. Edit Role\n";
            cout << "3. Edit Duty Position\n";
            cout << "4. Back\n";

            int choice = getValidatedChoice(1, 4);

            switch (choice) {
            case 1: { 
                string newStatus = getNonEmptyString("Set new attendance (Present/Absent): ");
                if (newStatus == "Present" || newStatus == "Absent") {
                    staff.attendance = newStatus;
                    cout << "(Success) Attendance updated.\n";
                }
                else {
                    cout << "Invalid status. No changes made.\n";
                }
                break;
            }
            case 2: {
                string newRole;
                while (true) {
                    newRole = getNonEmptyString("Enter new role (Manager, Chef, Waiter, Security): ");
                    if (newRole == "Manager" || newRole == "Chef" || newRole == "Waiter" || newRole == "Security") {
                        staff.role = newRole;
                        cout << "(Success) Role updated.\n";
                        break;
                    }
                    else {
                        cout << "Invalid role. Please choose from the specified options.\n";
                    }
                }
                break;
            }
            case 3: { 
                staff.dutyPlace = getNonEmptyString("Enter new duty position: ");
                cout << "(Success) Duty position updated.\n";
                break;
            }
            case 4: { 
                cout << "No changes made.\n";
                break;
            }
            }
            return; 
        }
    }
    cout << "Staff ID not found.\n";
}

// De-allocate a staff member from the event
void deallocateStaffFromEvent(Event& event) {
    viewEventStaff(event);
    string staffId = getNonEmptyString("\nEnter Staff ID to de-allocate: ");
    for (auto it = event.assignedStaff.begin(); it != event.assignedStaff.end(); ++it) {
        if (it->staffId == staffId) {
            event.assignedStaff.erase(it);
            cout << "(Success) Staff member has been de-allocated.\n";
            return;
        }
    }
    cout << "Staff ID not found.\n";
}
