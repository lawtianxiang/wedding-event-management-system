#ifndef REPORT_MODULE_H
#define REPORT_MODULE_H

#include <vector>
#include <string>
#include "structures.h"

using namespace std;

void handleReporting(vector<Event>& events);
void generateGuestReport(const vector<Event>& events);
void generateFinancialReport(const vector<Event>& events);
void generateEventAddOnReport(const vector<Event>& events);
void generateAnalysisReport(const vector<Event>& events);
void generateAdHocReport(const vector<Event>& events);
void deleteReportFile();
string getUniqueFilename(const string& baseName);
void addReportToManifest(const string& filename);

#endif 