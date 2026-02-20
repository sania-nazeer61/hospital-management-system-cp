#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
using namespace std;

class Doctor {
private:
    int id;
    string name;
    string specialization;
    string contact;
    bool available;

public:
    // Constructors
    Doctor(); 
    Doctor(int, string, string, string, bool);
    Doctor(const Doctor&);

    // Destructor
    ~Doctor();

    // Setters
    void setID(int);
    void setName(string);
    void setSpecialization(string);
    void setContact(string);
    void setAvailability(bool);

    // Getters
    int getID() const;
    string getName() const;
    string getSpecialization() const;
    string getContact() const;
    bool isAvailable() const;

    // Display details
    void display() const;
};

#endif

