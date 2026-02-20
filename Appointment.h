#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
#include "Patient.h"
#include "Doctor.h"

using namespace std;

class Appointment {
private:
    int id;
    Patient* patient;
    Doctor* doctor;
    string date;   // format: YYYY-MM-DD
    string time;   // format: HH:MM

public:
    // Constructors
    Appointment();
    Appointment(int, Patient*, Doctor*, string, string);
    Appointment(const Appointment&);

    // Destructor
    ~Appointment();

    // Setters
    void setID(int);
    void setPatient(Patient*);
    void setDoctor(Doctor*);
    void setDate(string);
    void setTime(string);

    // Getters
    int getID() const;
    Patient* getPatient() const;
    Doctor* getDoctor() const;
    string getDate() const;
    string getTime() const;

    // Display
    void display() const;
};

#endif

