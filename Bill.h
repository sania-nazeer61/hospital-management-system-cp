#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>
#include "Patient.h"
using namespace std;

class Bill {
private:
    int id;
    Patient* patient;
    double consultationFees;
    double medicineCosts;
    double testCosts;
    double paidAmount;

public:
    // Constructors
    Bill();
    Bill(int, Patient*, double, double, double, double);
    Bill(const Bill&);

    // Destructor
    ~Bill();

    // Setters
    void setID(int);
    void setPatient(Patient*);
    void setConsultationFees(double);
    void setMedicineCosts(double);
    void setTestCosts(double);
    void setPaidAmount(double);

    // Getters
    int getID() const;
    Patient* getPatient() const;
    double getConsultationFees() const;
    double getMedicineCosts() const;
    double getTestCosts() const;
    double getPaidAmount() const;

    // Functionalities
    double getTotalAmount() const;
    double getPendingAmount() const;
    void display() const;
};

#endif

