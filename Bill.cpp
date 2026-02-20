#include "Bill.h"
#include <iomanip>

// Default Constructor
Bill::Bill() {
    id=0; patient=NULL;
    consultationFees=0; medicineCosts=0; testCosts=0; paidAmount=0;
}

// Parameterized Constructor
Bill::Bill(int i, Patient* p, double c, double m, double t, double paid) {
    setID(i); setPatient(p); setConsultationFees(c);
    setMedicineCosts(m); setTestCosts(t); setPaidAmount(paid);
}

// Copy Constructor
Bill::Bill(const Bill &b) {
    id=b.id; patient=b.patient;
    consultationFees=b.consultationFees; medicineCosts=b.medicineCosts; 
    testCosts=b.testCosts; paidAmount=b.paidAmount;
}

// Destructor
Bill::~Bill() {}

// Setters
void Bill::setID(int i){ if(i>0) id=i; else id=0; }
void Bill::setPatient(Patient* p){ patient=p; }
void Bill::setConsultationFees(double c){ consultationFees=(c>=0)?c:0; }
void Bill::setMedicineCosts(double m){ medicineCosts=(m>=0)?m:0; }
void Bill::setTestCosts(double t){ testCosts=(t>=0)?t:0; }
void Bill::setPaidAmount(double p){ paidAmount=(p>=0)?p:0; }

// Getters
int Bill::getID() const { return id; }
Patient* Bill::getPatient() const { return patient; }
double Bill::getConsultationFees() const { return consultationFees; }
double Bill::getMedicineCosts() const { return medicineCosts; }
double Bill::getTestCosts() const { return testCosts; }
double Bill::getPaidAmount() const { return paidAmount; }

// Calculate total
double Bill::getTotalAmount() const {
    return consultationFees + medicineCosts + testCosts;
}

// Pending
double Bill::getPendingAmount() const {
    double pending = getTotalAmount() - paidAmount;
    return (pending>=0)? pending : 0;
}

// Display
void Bill::display() const {
    cout << left << setw(5) << id
         << setw(15) << (patient? patient->getName():"N/A")
         << setw(10) << consultationFees
         << setw(10) << medicineCosts
         << setw(10) << testCosts
         << setw(10) << paidAmount
         << setw(10) << getPendingAmount()
         << setw(10) << getTotalAmount()
         << endl;
}

