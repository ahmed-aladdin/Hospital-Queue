#include <iostream>

using namespace std;
const int MAX_Specialization = 20;
const int MAX_Queue = 5;

struct hospital_queue {
    string name[MAX_Queue];
    int status[MAX_Queue];
    int len, spec;

    hospital_queue() {
        len = 0, spec = -1;
    }

    hospital_queue(int spec_) {
        len = 0;
        spec = spec_;
    }

    bool add_back(string &name_, int status_) {
        if (len == MAX_Queue)
            return false;
        name[len] = name_;
        status[len] = status_;
        len++;
        return true;
    }

    bool add_fornt(string &name_, int status_) {
        if (len == MAX_Queue)
            return false;
        for (int i = len; i >= 1; --i) {
            name[i] = name[i - 1];
            status[i] = status[i - 1];
        }
        name[0] = name_;
        status[0] = status_;
        len++;
        return true;
    }

    void remove() {
        if (len == 0) {
            cout << "No patient at the moment, Have rest, Dr\n";
            return;
        }
        cout << name[0] << " please go with the Dr\n";

        for (int i = 1; i < len; ++i) {
            name[i - 1] = name[i];
            status[i - 1] = status[i];
        }
        len--;
    }

    void print() {
        if (len == 0)return;
        cout << "Specialization number : " << spec << "\n";
        for (int i = 0; i < len; i++) {
            cout << "name : " << name[i] << "\t";
            if (status[i])
                cout << "Urgent\n";
            else
                cout << "Regular\n";
        }
        cout << "\n";
    }
};

struct hospital_system {
    hospital_queue queues[MAX_Specialization];

    hospital_system() {
        for (int i = 0; i < MAX_Specialization; ++i) {
            queues[i] = hospital_queue(i);
        }
    }

    void run() {
        while (true) {
            int choice = menu();
            if (choice == 1)
                add_patient();
            else if (choice == 2)
                print_patients();
            else if (choice == 3)
                get_next_patient();
            else
                break;
        }
    }

    int menu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nEnter your choice\n";
            cout << "1) Add new patient\n";
            cout << "2) Print all patients\n";
            cout << "3) Get next patient\n";
            cout << "4) Exit\n";
            cin >> choice;
            if (choice < 1 || choice > 4) {
                cout << "Invalid choice, try again please!\n";
                choice = -1;
            }
        }
        return choice;
    }

    bool add_patient() {
        int spec, status;
        string name;
        cout << "Write 3 values specialization , name and status\n";
        cin >> spec >> name >> status;
        bool added;
        if (status)
            added = queues[spec].add_fornt(name, status);
        else
            added = queues[spec].add_back(name, status);

        if (!added) {
            cout << "Sorry we can't add more patients for this specification\n";
            return false;
        }
        return true;
    }

    void print_patients() {
        cout<<"*************************************\n";
        for (int i = 0; i < MAX_Specialization; ++i) {
            queues[i].print();
        }
    }

    void get_next_patient() {
        int spec;
        cout << "Enter specification : ";
        cin >> spec;
        queues[spec].remove();
    }
};

int main() {
    hospital_system hospital;
    hospital.run();
    return 0;
}
