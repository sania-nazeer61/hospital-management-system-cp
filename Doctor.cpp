#include "Doctor.h"
#include <iomanip>

// Default Constructor
Doctor::Doctor() {
    id = 0;
    name = "Unknown";
    specialization = "General";
    contact = "N/A";
    available = true;
}

// Parameterized Constructor
Doctor::Doctor(int i, string n, string s, string c, bool a) {
    setID(i); setName(n); setSpecialization(s); setContact(c); setAvailability(a);
}

// Copy Constructor
Doctor::Doctor(const Doctor &d) {
    id = d.id; name = d.name; specialization = d.specialization; contact = d.contact; available = d.available;
}

// Destructor
Doctor::~Doctor() {}

// Setters
void Doctor::setID(int i){ if(i>0) id=i; else id=0; }
void Doctor::setName(string n){ if(n!="") name=n; }
void Doctor::setSpecialization(string s){ specialization=s; }
void Doctor::setContact(string c){ contact=c; }
void Doctor::setAvailability(bool a){ available=a; }

// Getters
int Doctor::getID() const { return id; }
string Doctor::getName() const { return name; }
string Doctor::getSpecialization() const { return specialization; }
string Doctor::getContact() const { return contact; }
bool Doctor::isAvailable() const { return available; }

// Display details
void Doctor::display() const {
    cout << left << setw(10) << id 
         << setw(15) << name 
         << setw(15) << specialization 
         << setw(15) << contact 
         << (available?"Available":"Not Available") 
         << endl;
}

