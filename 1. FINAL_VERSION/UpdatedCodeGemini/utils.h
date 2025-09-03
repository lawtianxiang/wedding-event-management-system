#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "structures.h"

using namespace std;

void displayIntroduction();
void displayMenu();
void displayEndingMessage();
void pauseSystem();
Event* findEventById(vector<Event>& events, int id);

#endif 