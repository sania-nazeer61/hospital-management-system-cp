#include "Appointment.h"
#include <iomanip>

// Default Constructor
Appointment::Appointment() {
    id=0;
    patient=NULL;
    doctor=NULL;
    date="0000-00-00";
    time="00:00";
}

// Parameterized Constructor
Appointment::Appointment(int i, Patient* p, Doctor* d, string dt, string tm) {
    setID(i);
    setPatient(p);
    setDoctor(d);
    setDate(dt);
    setTime(tm);
}

// Copy Constructor
Appointment::Appointment(const Appointment &a) {
    id = a.id;
    patient = a.patient;
    doctor = a.doctor;
    date = a.date;
    time = a.time;
}

// Destructor
Appointment::~Appointment() {
    // No delete for patient/doctor, we don't own the memory
}

// Setters
void Appointment::setID(int i){ if(i>0) id=i; else id=0; }
void Appointment::setPatient(Patient* p){ patient = p; }
void Appointment::setDoctor(Doctor* d){ doctor = d; }
void Appointment::setDate(string d){ date=d; }
void Appointment::setTime(string t){ time=t; }

// Getters
int Appointment::getID() const { return id; }
Patient* Appointment::getPatient() const { return patient; }
Doctor* Appointment::getDoctor() const { return doctor; }
string Appointment::getDate() const { return date; }
string Appointment::getTime() const { return time; }

// Display appointment
void Appointment::display() const {
    cout << left << setw(5) << id
         << setw(15) << (patient? patient->getName() : "N/A")
         << setw(15) << (doctor? doctor->getName() : "N/A")
         << setw(12) << date
         << setw(8) << time
         << endl;
}

