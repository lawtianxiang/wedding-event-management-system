#ifndef STRUCTURES_H  
#define STRUCTURES_H  

#include <string>  
#include <vector>  
using namespace std;  

struct Task {  
    string description;  
    string status;  
};  

struct AddOn {  
    string description;  
    string status;  
};  

struct Client {  
    string name;  
    string contactNumber;  
};  

struct Payment {  
    int invoiceId = 0;  
    double amount = 0.00;  
    string status;  
    string method;  
};  

struct Staff {  
    string staffId;  
    string name;  
    string role;  
    string attendance;  
    string dutyPlace;  
};  

struct Event {  
    int eventId = 0;  
    Client client;  
    string eventDate;  
    string eventTime;  
    int estimatedGuests = 0;  
    string packageChoice;  
    vector<Staff> assignedStaff;  
    vector<string> guestList;  
    Payment paymentDetails;  
    vector<Task> tasks;  
}; 

#endif