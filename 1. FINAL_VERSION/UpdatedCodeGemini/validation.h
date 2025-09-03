#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

using namespace std;

int getValidatedInteger(const string& prompt);
double getValidatedDouble(const string& prompt);
string getNonEmptyString(const string& prompt);
char getValidatedYesNo(const string& prompt);
string getValidatedDate(const string& prompt);
int getValidatedChoice(int min, int max);
string getValidatedDate(const string& prompt);
string getValidatedPhoneNumber(const string& prompt);
string getValidatedTime(const string& prompt);
string getValidatedName(const string& prompt);
string getValidatedEBanking();
string getValidatedTnG();

#endif