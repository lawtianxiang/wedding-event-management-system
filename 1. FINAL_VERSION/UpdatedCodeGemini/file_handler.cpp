#include "file_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// save events to a file
void saveDataToFile(const vector<Event>& events) {
    ofstream outFile("events.txt");
    if (!outFile) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    for (const auto& event : events) {
		outFile << event.eventId << "|"
            << event.client.name << "|"
            << event.client.contactNumber << "|"
            << event.eventDate << "|"
            << event.eventTime << "|"
            << event.estimatedGuests << "|"
            << event.packageChoice << "|"
            << event.paymentDetails.invoiceId << "|"
            << event.paymentDetails.amount << "|"
            << event.paymentDetails.status << "|"
            << event.client.rating << "|"
            << event.client.feedback;

        for (const auto& staff : event.assignedStaff) {
            outFile << "||" << staff.staffId << "," << staff.name << "," << staff.role << "," << staff.attendance << "," << staff.dutyPlace;
        }
        for (const auto& guest : event.guestList) {
            outFile << "%%" << guest.name << "," << guest.contactNumber << "," << guest.rating << "," << guest.feedback;
        }
        for (const auto& task : event.tasks) {
            outFile << "##" << task.description << "," << task.status;
        }
        outFile << "\n";
    }
}

// load events from a file
void loadDataFromFile(vector<Event>& events) {
    ifstream inFile("events.txt");
    if (!inFile) {
        cerr << "Error: Could not open events.txt for reading.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string segment;
        Event tempEvent;

        // Core event fields
        getline(ss, segment, '|'); tempEvent.eventId = stoi(segment);
        getline(ss, tempEvent.client.name, '|');
        getline(ss, tempEvent.client.contactNumber, '|');
        getline(ss, tempEvent.eventDate, '|');
        getline(ss, tempEvent.eventTime, '|');
        getline(ss, segment, '|'); tempEvent.estimatedGuests = stoi(segment);
        getline(ss, tempEvent.packageChoice, '|');
        getline(ss, segment, '|'); tempEvent.paymentDetails.invoiceId = stoi(segment);
        getline(ss, segment, '|'); tempEvent.paymentDetails.amount = stod(segment);
        getline(ss, tempEvent.paymentDetails.status, '|');
        getline(ss, segment, '|'); tempEvent.client.rating = stod(segment);
        getline(ss, tempEvent.client.feedback, '|');

        // Remaining data (staff/tasks) if any
        string part;
        while (getline(ss, part, '|')) {
            if (!part.empty()) {
                stringstream staffStream(part);
                Staff tempStaff;
                getline(staffStream, tempStaff.staffId, ',');
                getline(staffStream, tempStaff.name, ',');
                getline(staffStream, tempStaff.role, ',');
                getline(staffStream, tempStaff.attendance, ',');
                getline(staffStream, tempStaff.dutyPlace); // last field
                tempEvent.assignedStaff.push_back(tempStaff);
            }
        }

        events.push_back(tempEvent);
    }

    inFile.close();
}
