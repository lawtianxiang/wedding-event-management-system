#include "payment_module.h"
#include "utils.h"
#include "validation.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// main menu for payment management
void handlePayments(vector<Event>& events) {
    int choice;
    do {
        cout << "\n--- Payment Management Menu ---\n";
        cout << "1. View All Payment Statuses\n";
        cout << "2. Manage a Specific Payment\n";
        cout << "3. Back to Main Menu\n";
        cout << "--------------------------------\n";
		choice = getValidatedChoice(1, 3);

        switch (choice) {
        case 1:
			viewAllPaymentStatuses(events);
            break;
        case 2:
			manageSinglePayment(events); 
            break;
        case 3:
			break;
        }
        if (choice != 3) {
            pauseSystem();
        }
    } while (choice != 3);
}

// view all payment statuses
void viewAllPaymentStatuses(const vector<Event>& events) {
    system("cls");
    cout << "--- All Payment Statuses ---\n";
    if (events.empty()) {
        cout << "No events found.\n";
        return;
    }

    cout << left << setw(10) << "Event ID" << setw(25) << "Client Name" << setw(15) << "Amount" << setw(15) << "Status" << endl;
    cout << string(65, '-') << endl;

    for (const auto& event : events) {
        cout << left << setw(10) << event.eventId
            << setw(25) << event.client.name
            << "$" << setw(13) << fixed << setprecision(2) << event.paymentDetails.amount
            << setw(15) << event.paymentDetails.status << endl;
    }
}

// manage payment for a specific event
void manageSinglePayment(vector<Event>& events) {
    int id = getValidatedInteger("\nEnter Event ID to manage payment: ");
    Event* event = findEventById(events, id);
    if (event == nullptr) {
        cout << "Event ID not found.\n";
        return;
    }
    cout << "\n--- Managing Payment for Event ID: " << id << " ---\n";
    cout << "Client: " << event->client.name << endl;
    cout << "Current Status: " << event->paymentDetails.status << endl;
    cout << "-------------------------------------------\n";
    cout << "1. Make Payment\n";
    cout << "2. Cancel Payment\n";
    cout << "3. Generate Invoice\n";
    cout << "4. Back\n";
    int choice = getValidatedChoice(1, 4);
    if (choice == 1) {  // make payment
        cout << "\nChoose Payment Method:\n";
        cout << "1. E-Banking\n";
        cout << "2. E-Wallet (TnG)\n";
        int methodChoice = getValidatedChoice(1, 2);

        string status;
        if (methodChoice == 1) {    // eBanking
			status = getValidatedEBanking();
        }
        else {  // eWallet
            status = getValidatedTnG();
        }
        event->paymentDetails.status = status;
    }
    else if (choice == 2) { //cancel payment
        event->paymentDetails.status = "Cancelled";
        cout << "(Success) Payment status updated to 'Cancelled'.\n";
    }
	else if (choice == 3) { //generate invoice
        generateInvoice(*event);
    }
}

void generateInvoice(const Event& event) {
    stringstream invoice;
    invoice << "=========================================================\n";
    invoice << "                       INVOICE\n";
    invoice << "=========================================================\n\n";
    invoice << "Invoice ID: " << event.paymentDetails.invoiceId << "\n";
    invoice << "Event ID:   " << event.eventId << "\n";
    invoice << "Date Issued: " << "Sunday, August 31, 2025" << "\n\n";
    invoice << "---------------------------------------------------------\n";
    invoice << "Bill To:\n";
    invoice << event.client.name << "\n";
    invoice << "Contact: " << event.client.contactNumber << "\n\n";
    invoice << "Event Details:\n";
    invoice << "Date: " << event.eventDate << " at " << event.eventTime << "\n\n";
    invoice << "---------------------------------------------------------\n";
    invoice << left << setw(40) << "Description" << setw(15) << "Amount" << "\n";
    invoice << string(57, '-') << "\n";
    invoice << left << setw(40) << ("Wedding Package - " + event.packageChoice) << "RM" << right << setw(13) << fixed << setprecision(2) << event.paymentDetails.amount << "\n\n";
    invoice << "---------------------------------------------------------\n";
    invoice << left << setw(40) << "TOTAL AMOUNT" << "RM" << right << setw(13) << fixed << setprecision(2) << event.paymentDetails.amount << "\n";
    invoice << "---------------------------------------------------------\n\n";
    invoice << "Payment Status: " << event.paymentDetails.status << "\n\n";
    invoice << "Thank you for your business!\n";
    invoice << "=========================================================\n";

    cout << "\n--- Generated Invoice ---\n" << invoice.str();
    string filename = "Invoice_Event_" + to_string(event.eventId) + ".txt";
    ofstream outFile(filename);
    outFile << invoice.str();
    cout << "\n(Success) Invoice saved to " << filename << endl;
}