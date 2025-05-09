#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int id;
    float grade;
    string letterGrade;
};

vector<Student> students;

string calculateLetterGrade(float grade) {
    if (grade >= 90) return "A+";
    if (grade >= 85) return "A";
    if (grade >= 80) return "A-";
    if (grade >= 75) return "B+";
    if (grade >= 70) return "B";
    if (grade >= 65) return "B-";
    if (grade >= 60) return "C+";
    if (grade >= 55) return "C";
    if (grade >= 50) return "C-";
    if (grade >= 45) return "D";
    return "F";
}

void saveToFile() {
    ofstream outFile("students.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }

    for (const auto& student : students) {
        outFile << student.name << "\n"
                << student.id << "\n"
                << student.grade << "\n";
    }
}

void addStudent() {
    Student newStudent;
    cout << "Enter student name: ";
    getline(cin, newStudent.name);
    
    cout << "Enter student ID: ";
    while (!(cin >> newStudent.id)) {
        cout << "Invalid input. Please enter a numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "Enter student grade (0-100): ";
    while (!(cin >> newStudent.grade) || newStudent.grade < 0 || newStudent.grade > 100) {
        cout << "Invalid grade. Please enter a value between 0-100: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    newStudent.letterGrade = calculateLetterGrade(newStudent.grade);
    
    if (any_of(students.begin(), students.end(), 
              [&newStudent](const Student& s) { return s.id == newStudent.id; })) {
        cout << "Student with ID " << newStudent.id << " already exists!\n";
        return;
    }
    
    students.push_back(newStudent);
    saveToFile();
    cout << "Student added successfully! (Grade: " << newStudent.letterGrade << ")\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }

    cout << "\nStudent Records:\n";
    cout << "---------------------------------------------\n";
    cout << "Name\t\tID\tScore\tGrade\n";
    cout << "---------------------------------------------\n";
    for (const auto& student : students) {
        cout << student.name << "\t" 
             << student.id << "\t"
             << student.grade << "\t"
             << student.letterGrade << "\n";
    }
}

void updateStudent() {
    if (students.empty()) {
        cout << "No students to update.\n";
        return;
    }

    int id;
    cout << "Enter student ID to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& student : students) {
        if (student.id == id) {
            cout << "Current: " << student.name << " (Grade: " << student.letterGrade << ")\n";
            cout << "Enter new name: ";
            getline(cin, student.name);
            
            cout << "Enter new grade (0-100): ";
            while (!(cin >> student.grade) || student.grade < 0 || student.grade > 100) {
                cout << "Invalid grade. Please enter a value between 0-100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            student.letterGrade = calculateLetterGrade(student.grade);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            saveToFile();
            cout << "Updated successfully! (New Grade: " << student.letterGrade << ")\n";
            return;
        }
    }
    cout << "Student with ID " << id << " not found.\n";
}

void deleteStudent() {
    if (students.empty()) {
        cout << "No students to delete.\n";
        return;
    }

    int id;
    cout << "Enter student ID to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = remove_if(students.begin(), students.end(),
                       [id](const Student& s) { return s.id == id; });
    
    if (it != students.end()) {
        students.erase(it, students.end());
        saveToFile();
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter 1-5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
        }
    } while (choice != 5);

    return 0;
}