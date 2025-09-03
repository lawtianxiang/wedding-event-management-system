#ifndef STAFF_MODULE_H
#define STAFF_MODULE_H

#include <vector>
#include "structures.h"

using namespace std;

void handleStaffManagement(vector<Event>& events);
void addStaffToEvent(Event& event);
void viewEventStaff(const Event& event);
void modifyStaffDetails(Event& event);
void deallocateStaffFromEvent(Event& event);

#endif 