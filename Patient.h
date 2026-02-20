#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
using namespace std;

class Patient {
private:
    int id;
    string name;
    int age;
    string contact;
    string medicalHistory;

public:
    // Constructors
    Patient();
    Patient(int, string, int, string, string);
    Patient(const Patient&);

    // Destructor
    ~Patient();

    // Setters
    void setID(int);
    void setName(string);
    void setAge(int);
    void setContact(string);
    void setMedicalHistory(string);

    // Getters
    int getID() const;
    string getName() const;
    int getAge() const;
    string getContact() const;
    string getMedicalHistory() const;

    // Display details
    void display() const;
};

#endif

