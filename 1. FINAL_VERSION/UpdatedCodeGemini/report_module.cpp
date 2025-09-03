#include "report_module.h"
#include "utils.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <sstream>
using namespace std;

const string REPORT_FOLDER = "reports/";
const string REPORT_MANIFEST = REPORT_FOLDER + "_report_manifest.txt";

// function to generate a unique filename when file name already exists
string getUniqueFilename(const string& baseName) {

	string filename = baseName + ".txt"; // initial filename
	ifstream file(filename); // check if file exists

    if (!file.good()) {
		return filename; // if not, return this filename
    }

	int counter = 1; // start counter for unique filenames
    while (true) { 
		filename = baseName + "_" + to_string(counter) + ".txt"; // generate new filename
		ifstream nextFile(filename); // check if this new filename exists
		if (!nextFile.good()) {
			return filename; // if not, return this filename
        }
		counter++; // increment counter and try again
    }
}

// function to append generated report filename to manifest file
void addReportToManifest(const string& filename) {

	ofstream manifestFile("_report_manifest.txt", ios::app); // open report manifest in append mode

    if (manifestFile) {
		manifestFile << filename << endl; // write filename to manifest
    }
}

// main menu for report generation
void handleReporting(vector<Event>& events) {
    
    int choice;

    do {
        cout << "\n--- Report Generation Menu ---\n";
        cout << "1. Generate Guest Management Report\n";
        cout << "2. Generate Financial Report\n";
        cout << "3. Generate Event Task Report\n";
        cout << "4. Generate Monthly Sales Analysis Report\n";
        cout << "5. Generate Ad-hoc (Custom) Event Report\n";
        cout << "6. Delete a Saved Report File\n";
        cout << "7. Back to Main Menu\n";
		choice = getValidatedChoice(1, 7); // get user choice with validation
        switch (choice) {
            case 1: 
				generateGuestReport(events); // generate guest management report
                break;
            case 2: 
				generateFinancialReport(events); // generate financial report
                break;
            case 3: 
				generateEventAddOnReport(events);  // generate event add-on service report
                break;
            case 4: 
				generateAnalysisReport(events); // generate monthly sales analysis report
                break;
            case 5: 
				generateAdHocReport(events); // generate ad-hoc custom report
                break;
            case 6: 
				deleteReportFile();  // delete a saved report file
                break;
            case 7: 
                break;
        }
		if (choice != 7) // if not exiting
			pauseSystem(); // pause before showing menu again
	} while (choice != 7); // loop until user chooses to exit
}

// generate guest management report
void generateGuestReport(const vector<Event>& events) {

	stringstream report; // use stringstream to build report content
	report << "--- Client Management Report ---\n\n"; // report header

    if (events.empty()) {
		report << "No events to report on.\n"; // handle no events case
    }
    else {
		report << left << setw(10) << "Event ID" << setw(25) << "Client" << setw(15) << "Contact" << setw(10) << "Guests" << endl; // table header
		report << string(60, '-') << endl; // separator line
        for (const auto& event : events) {
			report << left << setw(10) << event.eventId << setw(25) << event.client.name << setw(15) << event.client.contactNumber << setw(10) << event.estimatedGuests << endl; // event details
        }
    }

	cout << "\n" << report.str(); // display report on console
	string filename = getUniqueFilename("Guest_Report"); // generate guest report
	ofstream outFile(filename); // open file for writing
	outFile << report.str(); // write report content to file
	addReportToManifest(filename); // add filename to manifest
	cout << "\n(Success) Report saved to " << filename << endl; // success message
}

// generate financial report
void generateFinancialReport(const vector<Event>& events) {

	stringstream report; // use stringstream to build report content
	report << "--- Financial Report ---\n\n"; // report header

    if (events.empty()) {
		report << "No events to report on.\n"; // handle no events case
    }
    else {
		report << left << setw(10) << "Inv. ID" << setw(25) << "Client" << setw(15) << "Amount" << setw(15) << "Status" << endl; // table header
		report << string(65, '-') << endl; // separator line
		double totalCompleted = 0.0, totalPending = 0.0, totalFailed = 0.0; // totals for each status
        for (const auto& event : events) {
			report << left << setw(10) << event.paymentDetails.invoiceId << setw(25) << event.client.name << "RM" << setw(13) << fixed << setprecision(2) << event.paymentDetails.amount << setw(15) << event.paymentDetails.status << endl; // event payment details
			if (event.paymentDetails.status == "Completed") totalCompleted += event.paymentDetails.amount; // accumulate totals
			else if (event.paymentDetails.status == "Pending") totalPending += event.paymentDetails.amount;
            else if(event.paymentDetails.status == "Failed") totalFailed += event.paymentDetails.amount;
        }
		report << string(65, '-') << endl; // separator line
		report << "Total Revenue (Completed): RM" << fixed << setprecision(2) << totalCompleted << endl; // display totals revenue
		report << "Total Outstanding (Pending): RM" << fixed << setprecision(2) << totalPending << endl; // display totals outstanding
    }

	cout << "\n" << report.str(); // display report on console
	string filename = getUniqueFilename("Financial_Report"); // generate financial report
	ofstream outFile(filename); // open file for writing
	outFile << report.str(); // write report content to file
	addReportToManifest(filename); // add filename to manifest
	cout << "\n(Success) Report saved to " << filename << endl; // success message
}

// generate event add-on service report
void generateEventAddOnReport(const vector<Event>& events) {

	stringstream report; // use stringstream to build report content
	report << "--- Event Add On Report ---\n\n"; // report header

    if (events.empty()) {
		report << "No events to report on.\n"; // handle no events case
    }
    else {
        for (const auto& event : events) {
            report << "================================================\n";
			report << "Event ID: " << event.eventId << " | Client: " << event.client.name << "\n"; // event header
            report << "------------------------------------------------\n";
            if (event.tasks.empty()) {
				report << "No add on assigned for this event.\n"; // handle no tasks case
            }
            else {
				report << left << setw(40) << "Add On Description" << setw(15) << "Status" << endl; // table header
				report << string(55, '-') << endl; // separator line
				for (const auto& task : event.tasks) { // list each task
					report << left << setw(40) << task.description << setw(15) << task.status << endl; // task details
                }
            }
			report << "\n"; // extra newline between events
        }
    }

	cout << "\n" << report.str(); // display report on console
	string filename = getUniqueFilename("Add_On_Report"); // generate add-on report
	ofstream outFile(filename); // open file for writing
	outFile << report.str(); // write report content to file
	addReportToManifest(filename); // add filename to manifest
	cout << "\n(Success) Report saved to " << filename << endl; // success message
}

// generate monthly sales analysis report
void generateAnalysisReport(const vector<Event>& events) {

	string month; // month input in YYYY-MM format
    while (true) {
		month = getNonEmptyString("\nEnter month to analyze (e.g., YYYY-MM): "); // get month input
		if (month.length() == 7 && month[4] == '-') { // basic format validation
            break;
        }
        else {
			cout << "Invalid format. Please use YYYY-MM format.\n"; // prompt again if invalid
        }
    }

	vector<Event> filteredEvents; // events filtered by month and completed status

    for (const auto& event : events) {
        if (event.eventDate.rfind(month, 0) == 0 && event.paymentDetails.status == "Completed") {
			filteredEvents.push_back(event); // add matching events to filtered list
        }
    }

    sort(filteredEvents.begin(), filteredEvents.end(), [](const Event& a, const Event& b) {
		return a.paymentDetails.amount > b.paymentDetails.amount; // sort by sale amount descending
        });

	stringstream report; // use stringstream to build report content
	report << "--- Top Sales Analysis for " << month << " ---\n\n"; // report header

    if (filteredEvents.empty()) {
		report << "No completed sales found for the specified month.\n"; // handle no matching events case
    }
    else {
		report << left << setw(5) << "Rank" << setw(10) << "Event ID" << setw(25) << "Client" << setw(15) << "Sale Amount" << endl; // table header
		report << string(55, '-') << endl; // separator line
		int rank = 1; // rank counter
        for (const auto& event : filteredEvents) {
            if (rank > 10) break;
			report << left << setw(5) << rank++ << setw(10) << event.eventId << setw(25) << event.client.name << "RM" << fixed << setprecision(2) << event.paymentDetails.amount << endl; // event details
        }
    }

	cout << "\n" << report.str(); // display report on console
	string filename = "Sales_Analysis_" + month + ".txt"; // generate sales analysis report
	ofstream outFile(filename); // open file for writing
	outFile << report.str(); // write report content to file
	addReportToManifest(filename); // add filename to manifest
	cout << "\n(Success) Report saved to " << filename << endl; // success message
}

// generate ad-hoc custom report for a specific event
void generateAdHocReport(const vector<Event>& events) {

	int id = getValidatedInteger("\nEnter Event ID for custom report: "); // get event ID input
	const Event* event = nullptr; // pointer to the event to report on

    for (const auto& e : events) {
        if (e.eventId == id) {
			event = &e; // found the event
            break;
        }
    }

    if (event == nullptr) {
		cout << "Event ID not found.\n"; // handle event not found case
        return;
    }

    stringstream report;
	report << "--- Ad-hoc Report for Event ID: " << id << " ---\n\n"; // report header
	cout << "Select sections to include in the report:\n"; // prompt for sections to include
	char c_client = getValidatedYesNo("Include Client Details? (y/n): "); // get yes/no input for client details
	char c_guest = getValidatedYesNo("Include Guest List? (y/n): "); // get yes/no input for guest list
	char c_staff = getValidatedYesNo("Include Staff Roster? (y/n): "); // get yes/no input for staff roster
	char c_task = getValidatedYesNo("Include Task List? (y/n): "); // get yes/no input for task list

    if (tolower(c_client) == 'y') {
		report << "--- Client & Event Details ---\n"; // client details section
		report << "Client Name: " << event->client.name << "\n"; // client name
		report << "Contact: " << event->client.contactNumber << "\n"; // client contact
		report << "Date: " << event->eventDate << " at " << event->eventTime << "\n"; // event date/time
		report << "Package: " << event->packageChoice << "\n"; // event package
		report << "Payment: " << event->paymentDetails.status << " ($" << event->paymentDetails.amount << ")\n\n"; // payment details
    }

    if (tolower(c_guest) == 'y') {
		report << "--- Guest List (" << event->guestList.size() << "/" << event->estimatedGuests << ") ---\n"; // guest list section
		for (const auto& guest : event->guestList) report << "- " << guest << "\n"; // list each guest
		report << "\n"; // extra newline after section
    }

    if (tolower(c_staff) == 'y') {
		report << "--- Staff Roster ---\n"; // staff roster section
		for (const auto& staff : event->assignedStaff) report << "- " << staff.name << " (" << staff.role << ") at " << staff.dutyPlace << "\n"; // list each staff member
		report << "\n"; // extra newline after section
    }

    if (tolower(c_task) == 'y') {
		report << "--- Task List ---\n"; // task list section
		for (const auto& task : event->tasks) report << "- " << task.description << " [" << task.status << "]\n"; // list each task
		report << "\n"; // extra newline after section
    }

	cout << "\n" << report.str(); // display report on console
	string filename = "AdHoc_Report_Event_" + to_string(id) + ".txt"; // generate ad-hoc report
	ofstream outFile(filename); // open file for writing
	outFile << report.str(); // write report content to file
	addReportToManifest(filename); // add filename to manifest
	cout << "\n(Success) Report saved to " << filename << endl; // success message
}


// function to delete a saved report file
void deleteReportFile() {

	ifstream manifestFile("_report_manifest.txt"); // open report manifest file for reading

    if (!manifestFile) {
		cout << "No reports have been generated yet.\n"; // handle no manifest file case
        return;
    }

	vector<string> filenames; // list of report filenames
	string filename; // temp variable for reading filenames
	int count = 1; // counter for numbering reports
	cout << "\n--- Saved Reports ---\n"; // header

    while (manifestFile >> filename) {
		filenames.push_back(filename); // add filename to list
		cout << count++ << ". " << filename << endl; // display numbered list
    }

	manifestFile.close(); // close manifest file

    if (filenames.empty()) {
		cout << "No reports found.\n"; // handle empty manifest case
        return;
    }

	int choice = -1; // user choice for which report to delete

    while (choice < 0 || choice > filenames.size()) {
		choice = getValidatedInteger("Enter the number of the report to delete (0 to cancel): "); // get user choice with validation
        if (choice < 0 || choice > filenames.size()) {
			cout << "Invalid number. Please enter a number from the list.\n"; // prompt again if invalid
        }
    }

    if (choice > 0) {
		string fileToDelete = filenames[choice - 1]; // get selected filename
        if (remove(fileToDelete.c_str()) == 0) {
			cout << "(Success) File '" << fileToDelete << "' deleted successfully.\n"; // success message
			ofstream newManifest("_report_manifest.txt"); // open manifest for rewriting
            for (const auto& fn : filenames) {
                if (fn != fileToDelete) {
					newManifest << fn << endl; // rewrite all except deleted file
                }
            }
        }
        else {
			cerr << "Error deleting file.\n"; // error message if deletion fails
        }
    }
    else {
		cout << "Deletion cancelled.\n"; // cancellation message
    }
}
