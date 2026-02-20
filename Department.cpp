#include "Department.h"
#include <iomanip>

// Default Constructor
Department::Department() {
    id=0; name="Unknown";
    doctors=NULL; doctorCount=0;
}

// Parameterized Constructor
Department::Department(int i, string n) {
    id=i; name=n;
    doctors=NULL; doctorCount=0;
}

// Copy Constructor
Department::Department(const Department &d) {
    id=d.id; name=d.name; doctorCount=d.doctorCount;
    if(doctorCount>0){
        doctors=new Doctor*[doctorCount];
        for(int i=0;i<doctorCount;i++) doctors[i]=d.doctors[i];
    } else doctors=NULL;
}

// Destructor
Department::~Department() {
    delete[] doctors;
}

// Setters
void Department::setID(int i){ if(i>0) id=i; else id=0; }
void Department::setName(string n){ name=n; }

// Getters
int Department::getID() const { return id; }
string Department::getName() const { return name; }
int Department::getDoctorCount() const { return doctorCount; }
Doctor** Department::getDoctors() const { return doctors; }

// Add Doctor
void Department::addDoctor(Doctor* d){
    Doctor** temp = new Doctor*[doctorCount+1];
    for(int i=0;i<doctorCount;i++) temp[i]=doctors[i];
    temp[doctorCount]=d;
    delete[] doctors;
    doctors=temp; doctorCount++;
}

// Display Department Info
void Department::display() const {
    cout<<"Department ID: "<<id<<", Name: "<<name<<"\nDoctors:\n";
    if(doctorCount==0){ cout<<"No doctors assigned yet.\n"; return;}
    cout<<left<<setw(10)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Specialization"<<setw(15)<<"Contact"<<setw(10)<<"Status\n";
    for(int i=0;i<doctorCount;i++) doctors[i]->display();
}

