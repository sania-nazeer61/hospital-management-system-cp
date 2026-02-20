#include "MedicalRecord.h"
#include <iomanip>

// Default Constructor
MedicalRecord::MedicalRecord() {
    id=0; patient=NULL; diagnosis="None"; treatment="None"; prescription="None"; date="0000-00-00";
}

// Parameterized Constructor
MedicalRecord::MedicalRecord(int i, Patient* p, string d, string t, string pr, string dt) {
    setID(i);
    setPatient(p);
    setDiagnosis(d);
    setTreatment(t);
    setPrescription(pr);
    setDate(dt);
}

// Copy Constructor
MedicalRecord::MedicalRecord(const MedicalRecord &m) {
    id = m.id;
    patient = m.patient;
    diagnosis = m.diagnosis;
    treatment = m.treatment;
    prescription = m.prescription;
    date = m.date;
}

// Destructor
MedicalRecord::~MedicalRecord() {}

// Setters
void MedicalRecord::setID(int i){ if(i>0) id=i; else id=0; }
void MedicalRecord::setPatient(Patient* p){ patient = p; }
void MedicalRecord::setDiagnosis(string d){ diagnosis=d; }
void MedicalRecord::setTreatment(string t){ treatment=t; }
void MedicalRecord::setPrescription(string pr){ prescription=pr; }
void MedicalRecord::setDate(string dt){ date=dt; }

// Getters
int MedicalRecord::getID() const { return id; }
Patient* MedicalRecord::getPatient() const { return patient; }
string MedicalRecord::getDiagnosis() const { return diagnosis; }
string MedicalRecord::getTreatment() const { return treatment; }
string MedicalRecord::getPrescription() const { return prescription; }
string MedicalRecord::getDate() const { return date; }

// Display
void MedicalRecord::display() const {
    cout << left << setw(5) << id
         << setw(15) << (patient? patient->getName():"N/A")
         << setw(20) << diagnosis
         << setw(20) << treatment
         << setw(20) << prescription
         << setw(12) << date
         << endl;
}

