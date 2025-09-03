#ifndef PAYMENT_MODULE_H
#define PAYMENT_MODULE_H

#include <vector>
#include "structures.h"

using namespace std;

void handlePayments(vector<Event>& events);
void viewAllPaymentStatuses(const vector<Event>& events);
void manageSinglePayment(vector<Event>& events);
void generateInvoice(const Event& event);

#endif 