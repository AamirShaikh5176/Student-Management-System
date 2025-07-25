#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void inputStudent() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void displayStudent() const {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Course: " << course << endl;
    }
};

// Function to add a student to the file
void addStudent() {
    ofstream file("students.txt", ios::app);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }
    
    Student s;
    s.inputStudent();

    file << s.id << "," << s.name << "," << s.age << "," << s.course << endl;
    file.close();
    cout << "Student added successfully!\n";
}

// Function to display all students
void displayStudents() {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student s;
    string line;
    cout << "\nList of Students:\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        
        getline(ss, temp, ',');
        s.id = stoi(temp);
        getline(ss, s.name, ',');
        getline(ss, temp, ',');
        s.age = stoi(temp);
        getline(ss, s.course, ',');

        s.displayStudent();
    }
    
    file.close();
}

// Function to search for a student by ID
void searchStudent(int searchId) {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        s.id = stoi(temp);
        getline(ss, s.name, ',');
        getline(ss, temp, ',');
        s.age = stoi(temp);
        getline(ss, s.course, ',');

        if (s.id == searchId) {
            cout << "\nStudent Found:\n";
            s.displayStudent();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student with ID " << searchId << " not found!\n";

    file.close();
}

// Function to delete a student by ID
void deleteStudent(int deleteId) {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<Student> students;
    Student s;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        s.id = stoi(temp);
        getline(ss, s.name, ',');
        getline(ss, temp, ',');
        s.age = stoi(temp);
        getline(ss, s.course, ',');

        if (s.id == deleteId) {
            found = true;
            continue;  // Skip writing this student back
        }
        students.push_back(s);
    }
    
    file.close();

    if (!found) {
        cout << "Student with ID " << deleteId << " not found!\n";
        return;
    }

    ofstream outFile("students.txt");
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (const auto &stud : students) {
        outFile << stud.id << "," << stud.name << "," << stud.age << "," << stud.course << endl;
    }
    
    outFile.close();
    cout << "Student deleted successfully!\n";
}

int main() {
    int choice, id;

    do {
        cout << "\nBVDUCOEP Student Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> id;
                searchStudent(id);
                break;
            case 4:
                cout << "Enter Student ID to delete: ";
                cin >> id;
                deleteStudent(id);
                break;
            case 5:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
