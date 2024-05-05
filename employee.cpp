#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef struct employee {
    int empId;
    char name[50];
    char designation[50];
    int salary;
} employee;

typedef struct index_pair {
    int key;
    int position;
} index_pair;

class employeeDatabase {
    string data_file_name = "ind_employee_data.dat";
    string index_file_name = "ind_employee_index.dat";
   public:
    employeeDatabase();
    void addEmployee(int eid, char name[50], char dest[50], int sal);
    void searchEmployee(int);
    void deleteEmployee(int);
    bool isPresent(int);
    void display_all();
    employee readEmp(int pos);
};

employee employeeDatabase::readEmp(int pos) {
    fstream data_file(data_file_name, ios::binary | ios::in | ios::ate);
    employee emp;
    if (pos >= data_file.tellg() || pos == -1) {
        emp.empId = -1;
        return emp;
    }
    data_file.seekg(pos, ios::beg);
    data_file.read((char *)&emp, sizeof(emp));
    data_file.close();
    return emp;
}

employeeDatabase::employeeDatabase() {
    fstream data_file(data_file_name);
    fstream index_file(index_file_name);
    if (data_file.fail() | index_file.fail()) {
        cout << "Created a new file." << endl;
        data_file.open(data_file_name, ios::binary | ios::out | ios::app);
        index_file.open(index_file_name, ios::binary | ios::out | ios::app);
    } else {
        cout << "File already exists." << endl;
    }
    data_file.close();
    index_file.close();
}

void employeeDatabase::addEmployee(int eid, char name[50], char dest[50], int sal) {
    fstream data_file(data_file_name, ios::binary | ios::out | ios::app);
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current, temp;
    char *all_data;
    employee emp;
    int pos, ipos;
    bool update = false;

    while (index_file.read((char *)&current, sizeof(index_pair))) {
      
        if (current.key == eid) {
            if (current.position == -1) {
                ipos = (int)index_file.tellg() - sizeof(current);
                update = true;
                break;
            } else {
                cout << "Cannot add employee, already exists."
                     << endl;
                goto exit_addEmployee;
            }
        }
    }
    index_file.close();

    emp.empId = eid;
    strcpy(emp.name, name);
    strcpy(emp.designation, dest);
    emp.salary = sal;

    data_file.seekp(0, ios::end);
    pos = data_file.tellp();
    data_file.write((char *)&emp, sizeof(emp));
    current.key = eid;
    current.position = pos;
    // cout << pos << endl;
    if (update) {
        index_file.open(index_file_name, ios::binary | ios::out);
        index_file.seekp(ipos, ios::beg);
        index_file.write((char *)&current, sizeof(current));
    } else {
        bool written = false;
        // inserting record in sorted order
        vector<index_pair> index_pairs;
        index_file.open(index_file_name, ios::binary | ios::in);
        while (index_file.read((char *)&temp, sizeof(index_pair))) {
            if (!written and temp.key > eid) {
                written = true;
                index_pairs.push_back(current);
            }
            index_pairs.push_back(temp);
        }
        if (!written) {
            index_pairs.push_back(current);
        }

        index_file.clear();
        index_file.close();

        // write records
        index_file.open(index_file_name, ios::binary | ios::out);

        for (int i = 0; i < index_pairs.size(); i++) {
            current = index_pairs[i];
            if (current.position != -1) {
                index_file.write((char *)&current, sizeof(index_pair));
            }
        }
    }
    cout << "Employee added successfully." << endl;
// close and exit
exit_addEmployee:
    data_file.close();
    index_file.close();
}

void display_emp(employee emp) {
    cout << "ID:\t" << emp.empId << endl;
    cout << "Name:\t" << emp.name << endl;
    cout << "Designation:\t" << emp.designation << endl;
    cout << "Salary:\tRs. " << emp.salary << endl;
}

void employeeDatabase::searchEmployee(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current;
    int pos = -1;

    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            pos = current.position;
            break;
        }
    }

    employee emp = readEmp(pos);
    if (emp.empId == -1) {
        cout << "Employee does not exist." << endl;
    } else {
        cout << "--- EMPLOYEE FOUND ---" << endl;
        display_emp(emp);
        cout << "--- END OF RECORD ---" << endl;
    }

    index_file.close();
}

bool employeeDatabase::isPresent(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current;

    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            if (current.position == -1) {
                index_file.close();
                return false;
            } else {
                index_file.close();
                return true;
            }
        }
    }
    index_file.close();
    return false;
}

void employeeDatabase::deleteEmployee(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current; 
    bool deleted = false;
    vector<index_pair> pairs;

    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            deleted = true;
        } else {
            pairs.push_back(current);
        }
    }
    index_file.close();
    if (deleted) {
        index_file.open(index_file_name, ios::binary | ios::out);
        index_file.clear();
        index_file.seekp(0, ios::beg);

        for (int i = 0; i < pairs.size(); i++) {
            current = pairs[i];
            index_file.write((char *)&current, sizeof(index_pair));
        }
        index_file.close();
        cout << "Employee removed from record." << endl;
    } else {
        cout << "Employee does not exist in the record." << endl;
    }
}

void employeeDatabase::display_all() {
    fstream index_file(index_file_name, ios::binary | ios::in);
    fstream data_file(data_file_name, ios::binary | ios::in);
    index_pair current;
    employee emp;
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.position != -1) {
            data_file.seekg(current.position, ios::beg);
            data_file.read((char *)&emp, sizeof(emp));
            cout << emp.empId << " | " << emp.name << " | " << emp.designation
                 << " | " << emp.salary << endl;
        }
    }
    index_file.close();
    data_file.close();
}

int main() {
    employeeDatabase db;
    int eid, sal;
    char name[50], dest[50];
    int ch;
    do {
        cout << endl << "--- MAIN MENU ---" << endl;
        cout << "1 -> Add employee" << endl;
        cout << "2 -> Search employee" << endl;
        cout << "3 -> Delete employee" << endl;
        cout << "4 -> Display all" << endl;
        cout << "5 -> Exit" << endl;
        cout << "Choose an option (1-5):\t";
        cin >> ch;
        switch (ch) {
            case 1:
            reenter_eid:
                cout << "Employee ID:\t";
                cin >> eid;
                if (db.isPresent(eid)) {
                    cout << "Employee already exists in record. Please try again."
                         << endl;
                    goto reenter_eid;
                }
                cout << "Name:\t";
                cin >> name;
                cout << "Designation:\t";
                cin >> dest;
                cout << "Salary:\tRs. ";
                cin >> sal;

                db.addEmployee(eid, name, dest, sal);
                break;
            case 2:
                cout << "Employee ID:\t";
                cin >> eid;
                db.searchEmployee(eid);
                break;
            case 3:
                cout << "Employee ID:\t";
                cin >> eid;
                db.deleteEmployee(eid);
                break;
            case 4:
                db.display_all();
                break;
            case 5:
                cout << "\n\n// END OF CODE\n\n" << endl;
                break;
            default:
                cout << "Please choose a valid option (1-5)." << endl;
                break;
        }
    } while (ch != 5);

    return 0;
}