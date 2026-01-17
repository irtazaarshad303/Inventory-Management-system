#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX = 50;

//logo design
void clinicDesign() {
    for (int i = 0; i < 45; i++)
        cout << "=";
    cout << endl;

    cout << "     IZM GENERAL CLINIC MANAGEMENT SYSTEM     " << endl;

    for (int i = 0; i < 45; i++)
        cout << "=";
    cout << endl;
}

//base class
class Person {
protected:
    string name;
public:
    virtual void display() = 0;
};

//user class inhertiated from base class
class User : public Person {
protected:
    string username;
    string password;
public:
    void set(string u, string p, string n) {
        username = u;
        password = p;
        name = n;
    }
    bool login(string u, string p) {
        return (u == username && p == password);
    }
    void display() {
        cout << "User: " << name << endl;
    }
};

//Admin class inhertiated from the base class
class Admin : public User {
public:
    Admin() {
        set("irtaza", "1801", "Admin");
    }
    void display() {
        cout << "Admin logged in\n";
    }
};

//another child class inheritaed from the base class
class Doctor : public Person {
public:
    string specialization;

    void input() {
        cout << "Doctor Name: ";
        cin >> name;
        cout << "Specialization: ";
        cin >> specialization;
    }
    void display() {
        cout << "Doctor: " << name
            << " | Specialization: " << specialization << endl;
    }
};
//class for storing medicine
class Medicine {
public:
    string name;
    int qty;
    float price;
    int rackNo;

    void input() {
        cout << "Medicine Name: ";
        cin >> name;
        cout << "Quantity: ";
        cin >> qty;
        cout << "Price: ";
        cin >> price;
        cout << "Rack No: ";
        cin >> rackNo;
    }

    void display() {
        cout << name << " | Qty: " << qty
            << " | Price: " << price
            << " | Rack: " << rackNo << endl;
    }
};

//class for creating bill
class Bill {
public:
    float total;
    float discount() {
        return total - (total * 0.10);
    }
};

//internal hospital system
class HospitalSystem {
private:
    Medicine meds[MAX];
    Doctor doctors[MAX];

    int medCount;
    int docCount;

    bool loggedIn;
    int role;   // 1=Admin, 2=User, 3=User

public:
    HospitalSystem() {
        medCount = 0;
        docCount = 0;
        loggedIn = false;
        role = 0;
        loadMedicinesFromFile();
    }

    //for data stored in the txt file
    void saveMedicinesToFile() {
        ofstream file("medicines.txt");
        for (int i = 0; i < medCount; i++) {
            file << meds[i].name << " "
                << meds[i].qty << " "
                << meds[i].price << " "
                << meds[i].rackNo << endl;
        }
        file.close();
    }

    void loadMedicinesFromFile() {
        ifstream file("medicines.txt");
        while (file >> meds[medCount].name
            >> meds[medCount].qty
            >> meds[medCount].price
            >> meds[medCount].rackNo) {
            medCount++;
        }
        file.close();
    }

//security check
    void login() {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        Admin admin;
        User user, user1;
        user.set("zia", "1111", "User");
        user1.set("hamza", "2222", "User");

        if (admin.login(u, p)) {
            loggedIn = true;
            role = 1;
            admin.display();
        }
        else if (user.login(u, p)) {
            loggedIn = true;
            role = 2;
            cout << "Staff logged in\n";
        }
        else if (user1.login(u, p)) {
            loggedIn = true;
            role = 3;
            cout << "Staff logged in\n";
        }
        else {
            cout << "Wrong login! Access denied\n";
            loggedIn = false;
            role = 0;
        }
    }

 //viewing the doctor if avaible
    void addDoctor() {
        if (!loggedIn || role != 1) {
            cout << "Only Admin can add doctor\n";
            return;
        }
        doctors[docCount].input();
        docCount++;
        cout << "Doctor added\n";
    }

    void viewDoctors() {
        if (!loggedIn) {
            cout << "Login required\n";
            return;
        }
        for (int i = 0; i < docCount; i++)
            doctors[i].display();
    }

//if staff login 
    void addMedicine() {
        if (!loggedIn) {
            cout << "Login required\n";
            return;
        }
        meds[medCount].input();
        medCount++;
        cout << "Medicine added\n";
    }

    void viewMedicines() {
        if (!loggedIn) {
            cout << "Login required\n";
            return;
        }
        for (int i = 0; i < medCount; i++)
            meds[i].display();
    }

    void searchMedicine() {
        if (!loggedIn) {
            cout << "Login required\n";
            return;
        }
        string m;
        cout << "Enter medicine name: ";
        cin >> m;

        for (int i = 0; i < medCount; i++) {
            if (meds[i].name == m) {
                cout << "Found in Rack No: " << meds[i].rackNo << endl;
                return;
            }
        }
        cout << "Medicine not found\n";
    }

    void generateBill() {
        if (!loggedIn) {
            cout << "Login required\n";
            return;
        }

        string m;
        int q;
        cout << "Enter medicine name: ";
        cin >> m;
        cout << "Enter quantity: ";
        cin >> q;

        for (int i = 0; i < medCount; i++) {
            if (meds[i].name == m) {
                Bill b;
                b.total = meds[i].price * q;
                cout << "Total: " << b.total << endl;
                cout << "After 10% discount: " << b.discount() << endl;
                return;
            }
        }
        cout << "Medicine not found\n";
    }

    void logout() {
        loggedIn = false;
        role = 0;
        cout << "Logged out\n";
    }
};

//main function
int main() {
    HospitalSystem h;
    int choice;

    clinicDesign();//desinging function called

    do {
        cout << "\n1 Login";
        cout << "\n2 Add Doctor (Admin)";
        cout << "\n3 View Doctors";
        cout << "\n4 Add Medicine";
        cout << "\n5 View Medicines";
        cout << "\n6 Search Medicine";
        cout << "\n7 Generate Bill";
        cout << "\n8 Logout";
        cout << "\n0 Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) h.login();//login check
        else if (choice == 2) h.addDoctor();//if login (only admin)
        else if (choice == 3) h.viewDoctors();//all members
        else if (choice == 4) h.addMedicine();//if any stff member login 
        else if (choice == 5) h.viewMedicines();//if any stff member login 
        else if (choice == 6) h.searchMedicine();//if any stff member login 
        else if (choice == 7) h.generateBill();//if any stff member login 
        else if (choice == 8) h.logout();//if any stff member login 
        else if (choice == 0) cout << "Program Ended\n";
        else cout << "Invalid choice\n";

    } while (choice != 0);

    h.saveMedicinesToFile();//saves all the changes made
    cout << "CHANGES SAVED IN INVENTORY\n";
    return 0;
}
