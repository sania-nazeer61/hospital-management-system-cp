#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <string>
#include "Doctor.h"
using namespace std;

class Department {
private:
    int id;
    string name;
    Doctor** doctors; // dynamic array of doctor pointers
    int doctorCount;

public:
    // Constructors
    Department();
    Department(int, string);
    Department(const Department&);

    // Destructor
    ~Department();

    // Setters
    void setID(int);
    void setName(string);

    // Getters
    int getID() const;
    string getName() const;
    int getDoctorCount() const;
    Doctor** getDoctors() const;

    // Functionalities
    void addDoctor(Doctor* d);
    void display() const;
};

#endif

