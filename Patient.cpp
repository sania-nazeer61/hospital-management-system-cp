#include "Patient.h"
#include <iomanip>

// Default Constructor
Patient::Patient() {
    id = 0;
    name = "Unknown";
    age = 0;
    contact = "N/A";
    medicalHistory = "None";
}

// Parameterized Constructor
Patient::Patient(int i, string n, int a, string c, string m) {
    setID(i);
    setName(n);
    setAge(a);
    setContact(c);
    setMedicalHistory(m);
}

// Copy Constructor
Patient::Patient(const Patient &p) {
    id = p.id;
    name = p.name;
    age = p.age;
    contact = p.contact;
    medicalHistory = p.medicalHistory;
}

// Destructor
Patient::~Patient() {}

// Setters
void Patient::setID(int i) { if(i>0) id=i; else id=0; }
void Patient::setName(string n) { if(n!="") name=n; }
void Patient::setAge(int a) { if(a>0 && a<120) age=a; else age=0; }
void Patient::setContact(string c) { contact=c; }
void Patient::setMedicalHistory(string m) { medicalHistory=m; }

// Getters
int Patient::getID() const { return id; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getContact() const { return contact; }
string Patient::getMedicalHistory() const { return medicalHistory; }

// Display
void Patient::display() const {
    cout << left << setw(10) << id
         << setw(15) << name
         << setw(8) << age
         << setw(15) << contact
         << setw(20) << medicalHistory
         << endl;
}

