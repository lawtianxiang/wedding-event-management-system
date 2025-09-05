#ifndef GUEST_MODULE_H
#define GUEST_MODULE_H

#include <vector>
#include "structures.h"

using namespace std;

void handleGuestList(vector<Event>& events);
void addGuest(const Event& targetEvent);
void viewGuests(const Event& event);
void removeGuest(Event& event);

#endif