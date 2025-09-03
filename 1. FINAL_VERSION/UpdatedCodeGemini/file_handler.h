// file_handler.h
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include "structures.h"

using namespace std;

void saveDataToFile(const vector<Event>& events);
void loadDataFromFile(vector<Event>& events);

#endif // FILE_HANDLER_H