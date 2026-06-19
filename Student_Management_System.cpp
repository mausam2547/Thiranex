#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Student
{
public:
    int id;
    string name;
    int age;
    string course;

    void input()
    {
        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display()
    {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << age
             << setw(20) << course << endl;
    }
};

// Add Student
void addStudent()
{
    Student s;

    ofstream file("students.txt", ios::app);

    s.input();

    file << s.id << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();

    cout << "\nStudent Record Added Successfully!\n";
}

// Display Students
void displayStudents()
{
    ifstream file("students.txt");

    Student s;
    string line;

    cout << "\n-----------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Course" << endl;
    cout << "-----------------------------------------------------------\n";

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        s.display();
    }

    file.close();
}

// Search Student
void searchStudent()
{
    ifstream file("students.txt");

    int searchId;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchId;

    Student s;
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        if (s.id == searchId)
        {
            cout << "\nStudent Found:\n";
            cout << "ID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Age: " << s.age << endl;
            cout << "Course: " << s.course << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

// Update Student
void updateStudent()
{
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int updateId;
    bool found = false;

    cout << "\nEnter Student ID to Update: ";
    cin >> updateId;
    cin.ignore();

    Student s;
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        if (s.id == updateId)
        {
            cout << "\nEnter New Details:\n";
            s.input();
            found = true;
        }

        temp << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Record Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

// Delete Student
void deleteStudent()
{
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int deleteId;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteId;

    Student s;
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        if (s.id == deleteId)
        {
            found = true;
            continue;
        }

        temp << s.id << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Record Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

// Main Menu
int main()
{
    int choice;

    do
    {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}