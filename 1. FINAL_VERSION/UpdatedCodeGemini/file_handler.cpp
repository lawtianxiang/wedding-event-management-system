#include "file_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// save events to a file
void saveDataToFile(const vector<Event>& events) {
    ofstream outFile("events.txt");
    if (!outFile) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& event : events) {
        // Write core event info
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
            << event.client.rating << "|";

        string safeFeedback = event.client.feedback;
        replace(safeFeedback.begin(), safeFeedback.end(), '|', '/');
        replace(safeFeedback.begin(), safeFeedback.end(), ',', ';');
        outFile << safeFeedback << "\n";

        // Write each guest on a new line
        for (const auto& guest : event.guestList) {
            string safeGuestFeedback = guest.feedback;
            replace(safeGuestFeedback.begin(), safeGuestFeedback.end(), '|', '/');
            replace(safeGuestFeedback.begin(), safeGuestFeedback.end(), ',', ';');

            outFile << "%%" << guest.name << "," << guest.contactNumber << "," << guest.rating << "," << safeGuestFeedback << "\n";
        }

        // You can also write staff/tasks here if needed
    }

    outFile.close();
}

// load events from a file
void loadDataFromFile(vector<Event>& events) {
    ifstream inFile("events.txt");
    if (!inFile) {
        cerr << "Error: Could not open events.txt for reading.\n";
        return;
    }

    string line;
    Event tempEvent;
    bool eventInProgress = false;

    while (getline(inFile, line)) {
        if (line.rfind("%%", 0) == 0) {
            // Guest line
            stringstream guestStream(line.substr(2));
            Client tempGuest;
            getline(guestStream, tempGuest.name, ',');
            getline(guestStream, tempGuest.contactNumber, ',');
            string ratingStr;
            getline(guestStream, ratingStr, ',');
            try {
                tempGuest.rating = stod(ratingStr);
            }
            catch (...) {
                tempGuest.rating = 0.0;
            }
            getline(guestStream, tempGuest.feedback, ',');
            tempEvent.guestList.push_back(tempGuest);
        }
        else {
            // New event line
            if (eventInProgress) {
                events.push_back(tempEvent);
                tempEvent = Event(); // reset for next event
            }

            stringstream ss(line);
            string segment;
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

            eventInProgress = true;
        }
    }

    // Push last event
    if (eventInProgress) {
        events.push_back(tempEvent);
    }

    inFile.close();
}