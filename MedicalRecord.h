#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <iostream>
#include <string>
#include "Patient.h"
using namespace std;

class MedicalRecord {
private:
    int id;
    Patient* patient;
    string diagnosis;
    string treatment;
    string prescription;
    string date; // YYYY-MM-DD

public:
    // Constructors
    MedicalRecord();
    MedicalRecord(int, Patient*, string, string, string, string);
    MedicalRecord(const MedicalRecord&);

    // Destructor
    ~MedicalRecord();

    // Setters
    void setID(int);
    void setPatient(Patient*);
    void setDiagnosis(string);
    void setTreatment(string);
    void setPrescription(string);
    void setDate(string);

    // Getters
    int getID() const;
    Patient* getPatient() const;
    string getDiagnosis() const;
    string getTreatment() const;
    string getPrescription() const;
    string getDate() const;

    // Display
    void display() const;
};

#endif

