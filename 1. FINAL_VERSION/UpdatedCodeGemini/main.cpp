#include <iostream>
#include <vector>
#include "structures.h"
#include "utils.h"
#include "file_handler.h"
#include "event_module.h"
#include "payment_module.h"
#include "staff_module.h"
#include "report_module.h"
#include "guest_module.h"
#include "validation.h"

using namespace std;

int main() {
    vector<Event> allEvents;

	loadDataFromFile(allEvents);    // load existing data
	displayIntroduction();  // display welcome message

    int choice;
    do {
		displayMenu();  // show main menu
		choice = getValidatedChoice(1, 6);  // get user choice

        switch (choice) {
		case 1: handleEventRegistration(allEvents); break;  // event management
		case 2: handlePayments(allEvents); break;   // payment processing
		case 3: handleStaffManagement(allEvents); break;    // staff management
		case 4: handleReporting(allEvents); break;  // reporting
		case 5: handleGuestList(allEvents); break;  // guest list management
        case 6: break;
        }
        if (choice != 6) {
			pauseSystem();  // pause before returning to menu
        }

    } while (choice != 6);

	saveDataToFile(allEvents);  // save data before exiting
	displayEndingMessage();		// display goodbye message

    return 0;
}