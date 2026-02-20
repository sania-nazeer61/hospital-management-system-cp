#include <iostream>
#include <iomanip>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "Bill.h"
#include "Department.h"

using namespace std;

// ---------------- REPORTING FUNCTIONS ----------------
void patientSummary(Patient* patients, int patientCount){
    cout<<"\n==== PATIENT SUMMARY ====\n";
    if(patientCount==0){ cout<<"No Patients Available.\n"; return;}
    cout<<left<<setw(10)<<"ID"<<setw(15)<<"Name"<<setw(5)<<"Age"<<setw(15)<<"Contact"<<setw(20)<<"History\n";
    for(int i=0;i<patientCount;i++){
        patients[i].display();
    }
}

void doctorPerformance(Appointment* appointments, int appointmentCount, Doctor* doctors, int doctorCount){
    cout<<"\n==== DOCTOR PERFORMANCE ====\n";
    if(doctorCount==0){ cout<<"No Doctors Available.\n"; return;}
    for(int i=0;i<doctorCount;i++){
        int count=0;
        for(int j=0;j<appointmentCount;j++){
            if(appointments[j].getDoctor()==&doctors[i]) count++;
        }
        cout<<doctors[i].getName()<<" - Appointments: "<<count<<endl;
    }
}

void financialSummary(Bill* bills, int billCount){
    cout<<"\n==== FINANCIAL SUMMARY ====\n";
    double totalRevenue=0, pending=0;
    for(int i=0;i<billCount;i++){
        totalRevenue+=bills[i].getPaidAmount();
        pending+=bills[i].getPendingAmount();
    }
    cout<<"Total Revenue Collected: "<<totalRevenue<<endl;
    cout<<"Total Pending Amount: "<<pending<<endl;
}

void appointmentStats(Appointment* appointments, int appointmentCount, string date){
    cout<<"\n==== APPOINTMENTS ON "<<date<<" ====\n";
    int count=0;
    for(int i=0;i<appointmentCount;i++){
        if(appointments[i].getDate()==date){ appointments[i].display(); count++; }
    }
    if(count==0) cout<<"No appointments on this date.\n";
}

// ---------------- SECURITY ----------------
struct User {
    string username;
    string password;
    string role; // admin, doctor, receptionist
};

bool login(User users[], int userCount, string uname, string pass, string &role){
    for(int i=0;i<userCount;i++){
        if(users[i].username==uname && users[i].password==pass){
            role=users[i].role;
            return true;
        }
    }
    return false;
}

bool roleAccess(string userRole, string requiredRole){
    return userRole==requiredRole || userRole=="admin";
}

// ---------------- MAIN ----------------
int main(){
    // ---------------- DYNAMIC ARRAYS ----------------
    Patient* patients=NULL; int patientCount=0;
    Doctor* doctors=NULL; int doctorCount=0;
    Appointment* appointments=NULL; int appointmentCount=0;
    MedicalRecord* records=NULL; int recordCount=0;
    Bill* bills=NULL; int billCount=0;
    Department* departments=NULL; int departmentCount=0;

    // ---------------- USERS ----------------
    User users[3] = { {"admin","1234","admin"}, {"dr1","abcd","doctor"}, {"rec1","5678","receptionist"} };
    string currentRole, uname, pass;

    cout<<"==== HOSPITAL MANAGEMENT SYSTEM LOGIN ====\n";
    cout<<"Username: "; cin>>uname;
    cout<<"Password: "; cin>>pass;

    if(!login(users,3,uname,pass,currentRole)){
        cout<<"Invalid Login! Exiting...\n"; return 0;
    }
    cout<<"Login Successful! Role: "<<currentRole<<endl;

    int mainChoice;
    do{
        cout<<"\n==== MAIN MENU ====\n";
        cout<<"1. Patient Management\n2. Doctor Management\n3. Appointment Management\n4. Medical Records\n5. Billing Management\n6. Department Management\n7. Reporting & Analytics\n0. Exit\n";
        cout<<"Enter Choice: "; cin>>mainChoice;

        switch(mainChoice){
            // ---------------- PATIENT ----------------
            case 1: {
                if(!roleAccess(currentRole,"receptionist") && !roleAccess(currentRole,"admin")) { cout<<"Access Denied!\n"; break;}
                int choice;
                do{
                    cout<<"\n--- PATIENT MENU ---\n";
                    cout<<"1.Add Patient\n2.View Patient\n3.Update Patient\n4.Delete Patient\n5.Search Patient\n6.List All Patients\n0.Back\nChoice: "; cin>>choice;

                    if(choice==1){
                        Patient* temp=new Patient[patientCount+1];
                        for(int i=0;i<patientCount;i++) temp[i]=patients[i];
                        int id, age; string name, contact, history;
                        cout<<"Patient ID:"; cin>>id;
                        cout<<"Name:"; cin.ignore(); getline(cin,name);
                        cout<<"Age:"; cin>>age;
                        cout<<"Contact:"; cin>>contact;
                        cout<<"Medical History:"; cin.ignore(); getline(cin,history);
                        temp[patientCount]=Patient(id,name,age,contact,history);
                        delete[] patients; patients=temp; patientCount++;
                        cout<<"Patient Added!\n";
                    }
                    else if(choice==2){
                        int id; cout<<"Enter Patient ID:"; cin>>id;
                        bool found=false;
                        for(int i=0;i<patientCount;i++) if(patients[i].getID()==id){ patients[i].display(); found=true; break;}
                        if(!found) cout<<"Patient Not Found!\n";
                    }
                    else if(choice==3){
                        int id; cout<<"Enter Patient ID to Update: "; cin>>id;
                        bool found=false;
                        for(int i=0;i<patientCount;i++){
                            if(patients[i].getID()==id){
                                string name, contact, history; int age;
                                cout<<"New Name:"; cin.ignore(); getline(cin,name);
                                cout<<"New Age:"; cin>>age;
                                cout<<"New Contact:"; cin>>contact;
                                cout<<"New History:"; cin.ignore(); getline(cin,history);
                                patients[i]=Patient(id,name,age,contact,history);
                                found=true; cout<<"Patient Updated!\n"; break;
                            }
                        }
                        if(!found) cout<<"Patient Not Found!\n";
                    }
                    else if(choice==4){
                        int id; cout<<"Enter Patient ID to Delete: "; cin>>id;
                        bool found=false;
                        for(int i=0;i<patientCount;i++){
                            if(patients[i].getID()==id){
                                for(int j=i;j<patientCount-1;j++) patients[j]=patients[j+1];
                                patientCount--;
                                found=true;
                                cout<<"Patient Deleted!\n"; break;
                            }
                        }
                        if(!found) cout<<"Patient Not Found!\n";
                    }
                    else if(choice==5){
                        string name; cout<<"Enter Patient Name to Search: "; cin.ignore(); getline(cin,name);
                        bool found=false;
                        for(int i=0;i<patientCount;i++){
                            if(patients[i].getName()==name){ patients[i].display(); found=true;}
                        }
                        if(!found) cout<<"Patient Not Found!\n";
                    }
                    else if(choice==6){
                        if(patientCount==0){ cout<<"No Patients Available.\n"; continue;}
                        cout<<left<<setw(10)<<"ID"<<setw(15)<<"Name"<<setw(5)<<"Age"<<setw(15)<<"Contact"<<setw(20)<<"History\n";
                        for(int i=0;i<patientCount;i++) patients[i].display();
                    }

                }while(choice!=0);
                break;
            }

            // ---------------- DOCTOR ----------------
            case 2: {
                if(!roleAccess(currentRole,"doctor") && !roleAccess(currentRole,"admin")) { cout<<"Access Denied!\n"; break;}
                int choice;
                do{
                    cout<<"\n--- DOCTOR MENU ---\n";
                    cout<<"1.Add Doctor\n2.View Doctor\n3.Update Doctor\n4.Delete Doctor\n5.Search Doctor\n6.List All Doctors\n7.Check Availability\n0.Back\nChoice: "; cin>>choice;

                    if(choice==1){
                        Doctor* temp=new Doctor[doctorCount+1];
                        for(int i=0;i<doctorCount;i++) temp[i]=doctors[i];
                        int id; string name,spec,contact; bool avail;
                        cout<<"Doctor ID:"; cin>>id;
                        cout<<"Name:"; cin.ignore(); getline(cin,name);
                        cout<<"Specialization:"; getline(cin,spec);
                        cout<<"Contact:"; cin>>contact;
                        cout<<"Available (1/0):"; cin>>avail;
                        temp[doctorCount]=Doctor(id,name,spec,contact,avail);
                        delete[] doctors; doctors=temp; doctorCount++;
                        cout<<"Doctor Added!\n";
                    }
                    else if(choice==2){
                        int id; cout<<"Enter Doctor ID:"; cin>>id;
                        bool found=false;
                        for(int i=0;i<doctorCount;i++){
                            if(doctors[i].getID()==id){ doctors[i].display(); found=true; break;}
                        }
                        if(!found) cout<<"Doctor Not Found!\n";
                    }
                    else if(choice==3){
                        int id; cout<<"Enter Doctor ID to Update:"; cin>>id;
                        bool found=false;
                        for(int i=0;i<doctorCount;i++){
                            if(doctors[i].getID()==id){
                                string name,spec,contact; bool avail;
                                cout<<"New Name:"; cin.ignore(); getline(cin,name);
                                cout<<"New Specialization:"; getline(cin,spec);
                                cout<<"New Contact:"; cin>>contact;
                                cout<<"Available (1/0):"; cin>>avail;
                                doctors[i]=Doctor(id,name,spec,contact,avail);
                                found=true; cout<<"Doctor Updated!\n"; break;
                            }
                        }
                        if(!found) cout<<"Doctor Not Found!\n";
                    }
                    else if(choice==4){
                        int id; cout<<"Enter Doctor ID to Delete:"; cin>>id;
                        bool found=false;
                        for(int i=0;i<doctorCount;i++){
                            if(doctors[i].getID()==id){
                                for(int j=i;j<doctorCount-1;j++) doctors[j]=doctors[j+1];
                                doctorCount--;
                                found=true; cout<<"Doctor Deleted!\n"; break;
                            }
                        }
                        if(!found) cout<<"Doctor Not Found!\n";
                    }
                    else if(choice==5){
                        string name; cout<<"Enter Doctor Name to Search:"; cin.ignore(); getline(cin,name);
                        bool found=false;
                        for(int i=0;i<doctorCount;i++){
                            if(doctors[i].getName()==name){ doctors[i].display(); found=true;}
                        }
                        if(!found) cout<<"Doctor Not Found!\n";
                    }
                    else if(choice==6){
                        if(doctorCount==0){ cout<<"No Doctors Available.\n"; continue;}
                        cout<<left<<setw(10)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Specialization"<<setw(15)<<"Contact"<<setw(10)<<"Avail\n";
                        for(int i=0;i<doctorCount;i++) doctors[i].display();
                    }
                    else if(choice==7){
                        cout<<"Checking doctor availability:\n";
                        for(int i=0;i<doctorCount;i++){
                            cout<<doctors[i].getName()<<" - "<< (doctors[i].isAvailable()? "Available":"Not Available") << endl;
                        }
                    }

                }while(choice!=0);
                break;
            }

            // ---------------- APPOINTMENT ----------------
case 3: {
    if(!roleAccess(currentRole,"receptionist") && !roleAccess(currentRole,"admin") && !roleAccess(currentRole,"doctor")) {
        cout << "Access Denied!\n"; 
        break;
    }

    int choice;
    do {
        cout << "\n--- APPOINTMENT MENU ---\n";
        cout << "1.Add Appointment\n2.View Appointment\n3.Update Appointment\n4.Delete Appointment\n5.Search Appointment by Patient ID\n6.List All Appointments\n0.Back\nChoice: "; 
        cin >> choice;

        if(choice == 1) { // Add Appointment
            Appointment* temp = new Appointment[appointmentCount + 1];
            for(int i=0;i<appointmentCount;i++) temp[i] = appointments[i];

            int aid, pid, did;
            string date, time;

            cout << "Appointment ID: "; cin >> aid;
            cout << "Patient ID: "; cin >> pid;
            cout << "Doctor ID: "; cin >> did;
            cout << "Date (YYYY-MM-DD): "; cin >> date;
            cout << "Time (HH:MM): "; cin >> time;

           Patient* pptr = NULL;  // nullptr ko NULL se replace kiya
for(int i = 0; i < patientCount; i++){
    if(patients[i].getID() == pid){
        pptr = &patients[i];
        break;
    }
}


           Doctor* dptr = NULL;  // nullptr ko NULL se replace kiya
for(int i = 0; i < doctorCount; i++){
    if(doctors[i].getID() == did){
        dptr = &doctors[i];
        break;
    }
}


            if(pptr == NULL || dptr == NULL){
    cout << "Patient or Doctor not found! Cannot create appointment.\n";
    delete[] temp;
} else {
    temp[appointmentCount] = Appointment(aid, pptr, dptr, date, time);
    delete[] appointments;
    appointments = temp;
    appointmentCount++;
    cout << "Appointment Added!\n";
}

        }
        else if(choice == 2){ // View Appointment by ID
            int aid; cout << "Enter Appointment ID: "; cin >> aid;
            bool found = false;
            for(int i=0;i<appointmentCount;i++){
                if(appointments[i].getID() == aid){
                    appointments[i].display();
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Appointment Not Found!\n";
        }
        else if(choice == 3){ // Update Appointment
            int aid; cout << "Enter Appointment ID to Update: "; cin >> aid;
            bool found=false;
            for(int i=0;i<appointmentCount;i++){
                if(appointments[i].getID() == aid){
                    int pid, did; string date, time;
                    cout << "Patient ID: "; cin >> pid;
                    cout << "Doctor ID: "; cin >> did;
                    cout << "Date (YYYY-MM-DD): "; cin >> date;
                    cout << "Time (HH:MM): "; cin >> time;

                    Patient* pptr = NULL;
for(int j = 0; j < patientCount; j++){
    if(patients[j].getID() == pid){
        pptr = &patients[j];
        break;
    }
}

                    Doctor* dptr = NULL;
for(int j = 0; j < doctorCount; j++){
    if(doctors[j].getID() == did){
        dptr = &doctors[j];
        break;
    }
}


                    if(pptr == NULL || dptr == NULL){
    cout << "Patient or Doctor not found! Cannot update appointment.\n";
}
else{
    appointments[i] = Appointment(aid, pptr, dptr, date, time);
    cout << "Appointment Updated!\n";
}

                    found=true; break;
                }
            }
            if(!found) cout << "Appointment Not Found!\n";
        }
        else if(choice == 4){ // Delete Appointment
            int aid; cout << "Enter Appointment ID to Delete: "; cin >> aid;
            bool found=false;
            for(int i=0;i<appointmentCount;i++){
                if(appointments[i].getID() == aid){
                    for(int j=i;j<appointmentCount-1;j++) appointments[j]=appointments[j+1];
                    appointmentCount--;
                    found=true;
                    cout << "Appointment Deleted!\n";
                    break;
                }
            }
            if(!found) cout << "Appointment Not Found!\n";
        }
        else if(choice == 5){ // Search by Patient ID
            int pid; cout << "Enter Patient ID to Search: "; cin >> pid;
            bool found=false;
            for(int i=0;i<appointmentCount;i++){
                if(appointments[i].getPatient()->getID() == pid){
                    appointments[i].display();
                    found=true;
                }
            }
            if(!found) cout << "No Appointments Found!\n";
        }
        else if(choice == 6){ // List All
            if(appointmentCount==0){ cout << "No Appointments Available.\n"; continue;}
            cout << left << setw(10) << "ID" << setw(15) << "Patient" << setw(15) << "Doctor" << setw(15) << "Date" << setw(10) << "Time\n";
            for(int i=0;i<appointmentCount;i++) appointments[i].display();
        }

    }while(choice!=0);
    break;
}
// ---------------- MEDICAL RECORD ----------------
case 4: {
    if(!roleAccess(currentRole,"doctor") && !roleAccess(currentRole,"admin")) {
        cout<<"Access Denied!\n"; 
        break;
    }

    int choice;
    do{
        cout<<"\n--- MEDICAL RECORD MENU ---\n";
        cout<<"1.Add Record\n2.View Record\n3.Update Record\n4.Delete Record\n5.Search by Patient ID\n6.List All Records\n0.Back\nChoice: ";
        cin>>choice;

        if(choice==1){ // Add
            MedicalRecord* temp = new MedicalRecord[recordCount+1];
            for(int i=0;i<recordCount;i++) temp[i]=records[i];

            int rid,pid;
            string diagnosis,treatment;

            cout<<"Record ID: "; cin>>rid;
            cout<<"Patient ID: "; cin>>pid;
            cout<<"Diagnosis: "; cin.ignore(); getline(cin,diagnosis);
            cout<<"Treatment: "; getline(cin,treatment);

            Patient* pptr=NULL;
            for(int i=0;i<patientCount;i++){
                if(patients[i].getID()==pid){
                    pptr=&patients[i];
                    break;
                }
            }

            if(pptr==NULL){
                cout<<"Patient not found! Cannot create record.\n";
                delete[] temp;
            }
            else{
    string doctorName, date;
    cout << "Doctor Name: "; cin.ignore(); getline(cin, doctorName);
    cout << "Record Date (YYYY-MM-DD): "; getline(cin, date);

    temp[recordCount] = MedicalRecord(rid, pptr, diagnosis, treatment, doctorName, date);
    delete[] records;
    records = temp;
    recordCount++;
    cout << "Medical Record Added!\n";
}

        }

        else if(choice==2){ // View
            int rid; cout<<"Enter Record ID: "; cin>>rid;
            bool found=false;
            for(int i=0;i<recordCount;i++){
                if(records[i].getID()==rid){
                    records[i].display();
                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Record Not Found!\n";
        }

        else if(choice==3){ // Update
            int rid; cout<<"Enter Record ID to Update: "; cin>>rid;
            bool found=false;
            for(int i=0;i<recordCount;i++){
                if(records[i].getID()==rid){
                    int pid;
                    string diagnosis,treatment;
                    cout<<"Patient ID: "; cin>>pid;
                    cout<<"New Diagnosis: "; cin.ignore(); getline(cin,diagnosis);
                    cout<<"New Treatment: "; getline(cin,treatment);

                    Patient* pptr=NULL;
                    for(int j=0;j<patientCount;j++){
                        if(patients[j].getID()==pid){
                            pptr=&patients[j];
                            break;
                        }
                    }

                    if(pptr==NULL){
                        cout<<"Patient not found!\n";
                    }
                    else{
    string doctorName, date;
    cout << "Doctor Name: "; cin.ignore(); getline(cin, doctorName);
    cout << "Record Date (YYYY-MM-DD): "; getline(cin, date);

    records[i] = MedicalRecord(rid, pptr, diagnosis, treatment, doctorName, date);
    cout << "Medical Record Updated!\n";
}

                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Record Not Found!\n";
        }

        else if(choice==4){ // Delete
            int rid; cout<<"Enter Record ID to Delete: "; cin>>rid;
            bool found=false;
            for(int i=0;i<recordCount;i++){
                if(records[i].getID()==rid){
                    for(int j=i;j<recordCount-1;j++)
                        records[j]=records[j+1];
                    recordCount--;
                    cout<<"Record Deleted!\n";
                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Record Not Found!\n";
        }

        else if(choice==5){ // Search by Patient ID
            int pid; cout<<"Enter Patient ID: "; cin>>pid;
            bool found=false;
            for(int i=0;i<recordCount;i++){
                if(records[i].getPatient()->getID()==pid){
                    records[i].display();
                    found=true;
                }
            }
            if(!found) cout<<"No Records Found!\n";
        }

        else if(choice==6){ // List All
            if(recordCount==0){
                cout<<"No Medical Records Available.\n";
                continue;
            }
            for(int i=0;i<recordCount;i++)
                records[i].display();
        }

    }while(choice!=0);
    break;
}

// ---------------- BILLING ----------------
case 5: {
    if(!roleAccess(currentRole,"receptionist") && !roleAccess(currentRole,"admin")) { cout<<"Access Denied!\n"; break;}
    int choice;
    do{
        cout<<"\n--- BILLING MENU ---\n";
        cout<<"1.Add Bill\n2.View Bill\n3.Update Bill\n4.Delete Bill\n5.Search Bill\n6.List All Bills\n0.Back\nChoice: "; cin>>choice;

        if(choice==1){ // Add Bill
            Bill* temp = new Bill[billCount + 1];
            for(int i = 0; i < billCount; i++) temp[i] = bills[i];

            int id, pid;
            double total, paid;

            cout << "Bill ID: "; cin >> id;
            cout << "Patient ID: "; cin >> pid;
            cout << "Total Amount: "; cin >> total;
            cout << "Paid Amount: "; cin >> paid;

            // Find Patient pointer from patient ID
            Patient* pptr = NULL; // old style NULL
            for(int i = 0; i < patientCount; i++){
                if(patients[i].getID() == pid){
                    pptr = &patients[i];
                    break;
                }
            }

            if(pptr == NULL){  
                cout << "Patient not found! Cannot create bill.\n";
                delete[] temp;
            } else {
                double discount = 0.0; // Default discount
                double tax = 0.0;      // Default tax
                temp[billCount] = Bill(id, pptr, total, paid, discount, tax); // Full constructor
                delete[] bills;
                bills = temp;
                billCount++;
                cout << "Bill Added!\n";
            }
        }

        else if(choice==2){ // View Bill
            int id; cout << "Enter Bill ID: "; cin >> id;
            bool found=false;
            for(int i=0;i<billCount;i++){
                if(bills[i].getID() == id){ bills[i].display(); found=true; break;}
            }
            if(!found) cout<<"Bill Not Found!\n";
        }

        else if(choice==3){ // Update Bill
            int id; cout << "Enter Bill ID to Update: "; cin >> id;
            bool found=false;
            for(int i=0;i<billCount;i++){
                if(bills[i].getID() == id){
                    int pid; double total, paid;
                    cout << "Patient ID: "; cin >> pid;
                    cout << "Total Amount: "; cin >> total;
                    cout << "Paid Amount: "; cin >> paid;

                    // Find Patient pointer
                    Patient* pptr = NULL;
                    for(int j=0;j<patientCount;j++){
                        if(patients[j].getID() == pid){
                            pptr = &patients[j];
                            break;
                        }
                    }

                    if(pptr == NULL){ 
                        cout << "Patient not found! Cannot update bill.\n";
                    } else {
                        double discount=0.0, tax=0.0;
                        bills[i] = Bill(id, pptr, total, paid, discount, tax);
                        cout<<"Bill Updated!\n";
                    }

                    found=true; 
                    break;
                }
            }
            if(!found) cout<<"Bill Not Found!\n";
        }

        else if(choice==4){ // Delete Bill
            int id; cout<<"Enter Bill ID to Delete:"; cin>>id;
            bool found=false;
            for(int i=0;i<billCount;i++){
                if(bills[i].getID()==id){
                    for(int j=i;j<billCount-1;j++) bills[j]=bills[j+1];
                    billCount--;
                    found=true; cout<<"Bill Deleted!\n"; break;
                }
            }
            if(!found) cout<<"Bill Not Found!\n";
        }

        else if(choice==5){ // Search Bills by Patient ID
            int pid; cout<<"Enter Patient ID to Search Bills:"; cin>>pid;
            bool found=false;
            for(int i=0;i<billCount;i++){
                if(bills[i].getPatient()->getID() == pid){ 
                    bills[i].display(); 
                    found=true;
                }
            }
            if(!found) cout<<"No Bills Found!\n";
        }

        else if(choice==6){ // List all Bills
            if(billCount==0){ cout<<"No Bills Available.\n"; continue;}
            cout<<left<<setw(10)<<"ID"<<setw(10)<<"PatientID"<<setw(10)<<"Total"<<setw(10)<<"Paid"<<setw(10)<<"Pending\n";
            for(int i=0;i<billCount;i++) bills[i].display();
        }

    }while(choice!=0);
    break;
}

//department
case 6: {
    if(!roleAccess(currentRole,"admin")) { 
        cout<<"Access Denied!\n"; 
        break;
    }

    int choice;
    do{
        cout<<"\n--- DEPARTMENT MENU ---\n";
        cout<<"1.Add Department\n2.View Department\n3.Update Department\n4.Delete Department\n5.Search Department\n6.List All Departments\n0.Back\nChoice: ";
        cin>>choice;

        if(choice==1){ // Add
    Department* temp = new Department[departmentCount+1];
    for(int i=0;i<departmentCount;i++) temp[i]=departments[i];

    int id; 
    string name;

    cout<<"Department ID: "; cin>>id;
    cout<<"Department Name: "; cin.ignore(); getline(cin,name);

    temp[departmentCount] = Department(id,name);
    delete[] departments;
    departments = temp;
    departmentCount++;

    cout<<"Department Added!\n";
}


        else if(choice==2){ // View
            int id; cout<<"Enter Department ID: "; cin>>id;
            bool found=false;
            for(int i=0;i<departmentCount;i++){
                if(departments[i].getID()==id){
                    departments[i].display();
                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Department Not Found!\n";
        }

        else if(choice==3){ // Update
    int id; 
    cout<<"Enter Department ID to Update: "; 
    cin>>id;

    bool found=false;
    for(int i=0;i<departmentCount;i++){
        if(departments[i].getID()==id){
            string name;
            cout<<"New Department Name: "; 
            cin.ignore(); 
            getline(cin,name);

            departments[i] = Department(id,name);
            cout<<"Department Updated!\n";
            found=true;
            break;
        }
    }
    if(!found) cout<<"Department Not Found!\n";
}

        else if(choice==4){ // Delete
            int id; cout<<"Enter Department ID to Delete: "; cin>>id;
            bool found=false;
            for(int i=0;i<departmentCount;i++){
                if(departments[i].getID()==id){
                    for(int j=i;j<departmentCount-1;j++)
                        departments[j]=departments[j+1];
                    departmentCount--;
                    cout<<"Department Deleted!\n";
                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Department Not Found!\n";
        }

        else if(choice==5){ // Search
            string name; 
            cout<<"Enter Department Name to Search: ";
            cin.ignore(); getline(cin,name);
            bool found=false;
            for(int i=0;i<departmentCount;i++){
                if(departments[i].getName()==name){
                    departments[i].display();
                    found=true;
                }
            }
            if(!found) cout<<"Department Not Found!\n";
        }

        else if(choice==6){ // List All
            if(departmentCount==0){
                cout<<"No Departments Available.\n";
                continue;
            }
            cout<<left<<setw(10)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Head\n";
            for(int i=0;i<departmentCount;i++)
                departments[i].display();
        }

    }while(choice!=0);
    break;
}

            // ---------------- REPORTING ----------------
            case 7: {
                int rchoice;
                do{
                    cout<<"\n--- REPORTING MENU ---\n";
                    cout<<"1.Patient Summary\n2.Doctor Performance\n3.Financial Summary\n4.Appointment Stats\n0.Back\nChoice: "; cin>>rchoice;
                    if(rchoice==1) patientSummary(patients,patientCount);
                    else if(rchoice==2) doctorPerformance(appointments,appointmentCount,doctors,doctorCount);
                    else if(rchoice==3) financialSummary(bills,billCount);
                    else if(rchoice==4){
                        string date; cout<<"Enter Date (YYYY-MM-DD): "; cin>>date;
                        appointmentStats(appointments,appointmentCount,date);
                    }
                }while(rchoice!=0);
                break;
            }

            case 0: break;
            default: cout<<"Invalid Choice!\n";
        }

    }while(mainChoice!=0);

    // ---------------- FREE MEMORY ----------------
    delete[] patients;
    delete[] doctors;
    delete[] appointments;
    delete[] records;
    delete[] bills;
    delete[] departments;

    cout<<"Exiting System...\n";
    return 0;
}





