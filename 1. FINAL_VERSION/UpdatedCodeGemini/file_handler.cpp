#include "file_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// save events to a file
void saveDataToFile(const vector<Event>& events) {
    ofstream outFile("events.txt");
    if (!outFile) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    for (const auto& event : events) {
        outFile << event.eventId << "|" << event.client.name << "|" << event.client.contactNumber << "|"
            << event.eventDate << "|" << event.eventTime << "|" << event.estimatedGuests << "|"
            << event.packageChoice << "|" << event.paymentDetails.invoiceId << "|"
            << event.paymentDetails.amount << "|" << event.paymentDetails.status;
        for (const auto& staff : event.assignedStaff) {
            outFile << "||" << staff.staffId << "," << staff.name << "," << staff.role << "," << staff.attendance << "," << staff.dutyPlace;
        }
        for (const auto& guest : event.guestList) {
            outFile << "%%" << guest;
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
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string segment;
        Event tempEvent;

        getline(ss, segment, '|'); tempEvent.eventId = stoi(segment);
        getline(ss, tempEvent.client.name, '|');
        getline(ss, tempEvent.client.contactNumber, '|');
        getline(ss, tempEvent.eventDate, '|');
        getline(ss, tempEvent.eventTime, '|');
        getline(ss, segment, '|'); tempEvent.estimatedGuests = stoi(segment);
        getline(ss, tempEvent.packageChoice, '|');
        getline(ss, segment, '|'); tempEvent.paymentDetails.invoiceId = stoi(segment);
        getline(ss, segment, '|'); tempEvent.paymentDetails.amount = stod(segment);

        string remainingData;
        getline(ss, remainingData);
        stringstream remainingStream(remainingData);
        getline(remainingStream, tempEvent.paymentDetails.status, '|');

        string part;
        while (getline(remainingStream, part, '|')) {
            if (part.rfind('%', 0) == 0) {
                tempEvent.guestList.push_back(part.substr(1));
            }
            else if (part.rfind('#', 0) == 0) {
                stringstream taskStream(part.substr(1));
                Task tempTask;
                getline(taskStream, tempTask.description, ',');
                getline(taskStream, tempTask.status, ',');
                tempEvent.tasks.push_back(tempTask);
            }
            else if (!part.empty()) {
                stringstream staffStream(part);
                Staff tempStaff;
                getline(staffStream, tempStaff.staffId, ',');
                getline(staffStream, tempStaff.name, ',');
                getline(staffStream, tempStaff.role, ',');
                getline(staffStream, tempStaff.attendance, ',');
                getline(staffStream, tempStaff.dutyPlace, ',');
                tempEvent.assignedStaff.push_back(tempStaff);
            }
        }
        events.push_back(tempEvent);
    }
}