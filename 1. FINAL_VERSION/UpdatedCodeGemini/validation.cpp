#include "validation.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

// validation for various input types
int getValidatedInteger(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// validation for double input
double getValidatedDouble(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number (e.g., 5000.00): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// validation for non-empty string input
string getNonEmptyString(const string& prompt) {
    string input;
    cout << prompt;
    while (getline(cin, input) && (input.empty() || input.find_first_not_of(" \t") == string::npos)) {
        cout << "Input cannot be empty. Please try again: ";
    }
    return input;
}

// validation for yes/no input
char getValidatedYesNo(const string& prompt) {
    char input;
    cout << prompt;
    while (cin >> input && tolower(input) != 'y' && tolower(input) != 'n') {
        cout << "Invalid input. Please enter 'y' or 'n': ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tolower(input);
}

// validation for date input in YYYY-MM-DD format
string getValidatedDate(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.length() == 10 && input[4] == '-' && input[7] == '-') {
            break;
        }
        else {
            cout << "Invalid format. Please use YYYY-MM-DD format.\n";
        }
    }
    return input;
}

// validation for menu choice input within a range
int getValidatedChoice(int min, int max) {
    int choice;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < min || choice > max) {
        cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// validation for phone number input (10 or 11 digits, +, -, spaces)
string getValidatedPhoneNumber(const string& prompt) {
    string input;
    while (true) {
        input = getNonEmptyString(prompt);

        // Check for invalid characters
        if (input.find_first_not_of("0123456789+- ") != string::npos) {
            cout << "Invalid characters. Phone number can only contain digits, '+', '-', and spaces.\n";
            continue;
        }

        // Remove non-digit characters
        string digitsOnly;
        for (char ch : input) {
            if (isdigit(ch)) {
                digitsOnly += ch;
            }
        }

        // Check length and prefix
        if ((digitsOnly.length() == 10 || digitsOnly.length() == 11) &&
            digitsOnly.substr(0, 2) == "01") {
            return digitsOnly;  // Return cleaned number
        }
        else {
            cout << "Invalid phone number! Must start with '01' and contain 10 or 11 digits.\n";
        }
    }
}

// validation for time input in HH:MM format
string getValidatedTime(const string& prompt) {
    string input;
    while (true) {
        input = getNonEmptyString(prompt);
        if (input.length() == 5 && input[2] == ':' && isdigit(input[0]) && isdigit(input[1]) && isdigit(input[3]) && isdigit(input[4])) {
            int hh = stoi(input.substr(0, 2));
            int mm = stoi(input.substr(3, 2));
            if (hh >= 0 && hh <= 23 && mm >= 0 && mm <= 59) {
                break; // Valid time
            }
        }
        cout << "Invalid time. Please use a valid HH:MM format (e.g., 14:30).\n";
    }
    return input;
}

//validation for name input (no digits allowed)
string getValidatedName(const string& prompt) {
    string input;
    while (true) {
        input = getNonEmptyString(prompt);
        // Check if any character is a digit
        if (input.find_first_of("0123456789") == string::npos) {
            break;
        }
        else {
            cout << "Invalid name. Names cannot contain numbers.\n";
        }
    }
    return input;
}

// validation for eBanking payment (10-digit account number, min 6-char password)
string getValidatedEBanking() {
    string accNum, bankName, password;
    bankName = getNonEmptyString("Enter Bank Name (eg: Public Bank): ");
    getline(cin, bankName);
    cout << "Enter Account Number (10 digits): ";
    getline(cin, accNum);

    if (accNum.length() == 10 && all_of(accNum.begin(), accNum.end(), ::isdigit)) {
        cout << "Enter your password (min 6 chars): ";
        getline(cin, password);

        if (password.length() >= 6) {
            cout << "E-Banking payment successful!\n";
            return "Completed";
        }
        else {
            cout << "Invalid password! Payment failed!\n";
            return "Failed";
        }
    }
    else {
        cout << "Invalid account number! Payment failed!\n";
        return "Failed";
    }
}

// validation for TnG eWallet payment (10-digit phone number, 6-digit PIN)
string getValidatedTnG() {
    string phoneNo;
    cout << "Enter your registered phone number (0123456789): ";
    getline(cin, phoneNo);

    if ((phoneNo.length() == 10 || phoneNo.length() == 11) &&
        phoneNo.substr(0, 2) == "01" &&
        all_of(phoneNo.begin(), phoneNo.end(), ::isdigit)) {

        string pin;
        cout << "Enter your 6-digit PIN: ";
        getline(cin, pin);

        if (pin.length() == 6 && all_of(pin.begin(), pin.end(), ::isdigit)) {
            cout << "E-Wallet payment successful!\n";
            return "Completed";
        }
        else {
            cout << "Invalid PIN! Payment failed!\n";
            return "Failed";
        }
    }
    else {
        cout << "Invalid phone number! Payment failed!\n";
        return "Failed";
    }
}
