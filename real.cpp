#include <iostream>
#include <string>
using namespace std;

class StudentNode
{
public:
    int roll;
    string name;
    float attendance;
    string feeStatus;
    StudentNode *next;

    StudentNode(int r, string n, float att, string fee)
    {
        roll = r;
        name = n;
        attendance = att;
        feeStatus = fee;
        next = nullptr;
    }
};

class StudentList
{
public:
    StudentNode *head;

    StudentList()
    {
        head = nullptr;
    }

    // Add student
    void addStudent()
    {
        int roll;
        string name, feeStatus;
        float attendedClasses;
        const int totalClasses = 48;

        cout << "\nEnter Roll Number: ";
        cin >> roll;
        cin.ignore(); // clear newline

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Attended Classes: ";
        cin >> attendedClasses;
        cin.ignore(); // clear newline before reading feeStatus

        if (attendedClasses > totalClasses)
        {
            cout << "You have entered more classes than total!\n";
            return;
        }

        cout << "Enter Fee Status (Paid/Pending): ";
        getline(cin, feeStatus);

        float attendancePercent = (attendedClasses / totalClasses) * 100;

        StudentNode *newNode = new StudentNode(roll, name, attendancePercent, feeStatus);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            StudentNode *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        cout << "Student added successfully! " << endl;
    }

    // Show all students
    void showStudents()
    {
        if (head == nullptr)
        {
            cout << "\nNo students in the list!\n";
            return;
        }

        cout << "\n--- Student List ---\n";
        StudentNode *temp = head;
        while (temp != nullptr)
        {
            cout << "Roll: " << temp->roll
                 << ", Name: " << temp->name
                 << ", Attendance: " << temp->attendance << "%"
                 << ", Fee: " << temp->feeStatus << endl;
            temp = temp->next;
        }
    }
    void updatestudent()
    {
    }
    void deletestudent()
    {
    }
    void sortbyrollno()
    {
    }
    void searchbyrollno()
    {
    }

    void showAttendance()
    {
        int rollNo;
        cout << "Enter rollno:" << endl;
        cin >> rollNo;
        if (head == nullptr)
        {
            cout << "No students in the list!\n";
            return;
        }

        StudentNode *temp = head;
        while (temp != nullptr)
        {
            if (temp->roll == rollNo)
            {
                cout << "Attendance: " << temp->attendance << "%\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Student with Roll Number " << rollNo << " not found.\n";
    }
};

// ----- Main Menu -----
int main()
{
    StudentList list;
    int choice;

    do
    {
        cout << "\n===== Student Management Menu =====";
        cout << "\n1. Add Student";
        cout << "\n2. Show All Students";
        cout << "\n3. update Student";
        cout << "\n4. delete Students";
        cout << "\n5. sort by roll no ";
        cout << "\n6. search by roll no ";
        cout << "\n7. search for attendance ";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        if (choice == 1)
            list.addStudent();
        else if (choice == 2)
            list.showStudents();
        else if (choice == 7)
            list.showAttendance();

        else
            cout << "Invalid choice! Try again.\n";

    } while (choice != 3);

    return 0;
}