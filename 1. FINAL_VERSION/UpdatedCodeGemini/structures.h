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
    double rating = 0.0;
    string feedback;
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
    int eventId;
    Client client;
    string eventDate;
    string eventTime;
    int estimatedGuests;
    string packageChoice;
    Payment paymentDetails;
    vector<Client> guestList;
    vector<Staff> assignedStaff;
    vector<Task> tasks;
};


#endif