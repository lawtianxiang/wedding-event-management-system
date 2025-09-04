#ifndef EVENT_MODULE_H
#define EVENT_MODULE_H

#include <vector>
#include "structures.h"
#include <iostream>

using namespace std;

void handleEventRegistration(vector<Event>& events);
void registerNewEvent(vector<Event>& events);
void viewAllEvents(const vector<Event>& events);
void updateEventInfo(vector<Event>& events);
void cancelEvent(vector<Event>& events);
void addOn(vector<Event>& events);
void addTaskToEvent(Event& event);
void displayPackageComparison();

#endif 
