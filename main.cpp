#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Node
{
public:
    string Name;
    int rollNo;
    float cgpa;
    int attendance;
    // string feeStatus;
    Node *next = nullptr;

    Node(string n, int r, float c, int a)
    {
        Name = n;
        rollNo = r;
        cgpa = c;
        attendance = a;
        // feeStatus = fee;
    }
};

class StudentList
{
public:
    Node *head;
    StudentList()
    {
        head = nullptr;
    }
    int countstudents()
    {
        int n = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            n++;
            temp = temp->next;
        }
        return n;
    }
    void insertStudent() // Node *&head
    {
        string name;
        int rollNo;
        float cgpa;
        // string feeStatus;
        float attendedClasses;
        const int totalClasses = 48;

        cout << "-----------------------------" << endl;
        cout << "         NEW STUDENT         " << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Roll Number: ";
        cin >> rollNo;

        if (isRollExist(rollNo))
        {
            cout << "This Roll Number already exists! Roll Number must be UNIQUE.\n";
            return;
        }

        cout << "CGPA (0.0 - 4.0): ";
        cin >> cgpa;
        while (cgpa < 0.0 || cgpa > 4.0)
        {
            cout << "Invalid CGPA. Enter again: ";
            cin >> cgpa;
        }

        cout << "Enter Attended Classes: ";
        cin >> attendedClasses;
        cin.ignore();
        if (attendedClasses > totalClasses)
        {
            cout << "You have entered more classes than total!\n";
            return;
        }

        /*  cout << "Enter Fee Status (Paid/Pending): ";
          getline(cin, feeStatus);*/

        float attendancePercent = (attendedClasses / (float)totalClasses) * 100;

        Node *new_node = new Node(name, rollNo, cgpa, attendancePercent);

        if (head == nullptr)
        {
            head = new_node;
            return;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        cout << "Student added successfully! " << endl;
    }

    void displayStudents(Node *head)
    {
        if (head == nullptr)
        {
            cout << "\n----------------------No Record Found-------------------------\n";
            return;
        }

        cout << "\n---------------------------Student List------------------------\n";

        cout << left
             << "| " << setw(20) << "Name"
             << "| " << setw(10) << "Roll No"
             << "| " << setw(10) << "CGPA"
             << "| " << setw(12) << "Attendance" << " |\n";

        cout << "-----------------------------------------------------------------\n";

        Node *temp = head;
        while (temp != nullptr)
        {
            cout << left
                 << "| " << setw(20) << temp->Name
                 << "| " << setw(10) << temp->rollNo
                 << "| " << setw(10) << temp->cgpa
                 << "| " << setw(12) << temp->attendance << " |\n";

            temp = temp->next;
        }
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

        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->rollNo == rollNo)
            {
                cout << "Attendance: " << temp->attendance << "%\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Student with Roll Number " << rollNo << " not found.\n";
    }

    //====================================================================================================
    void searchStudent_ByGPA()
    {
        int choice;
        cout << "\n1) Search Student By CGPA Range";
        cout << "\n2) Search Student By Exact CGPA\n";
        cout << "Enter your choice" << " ";
        cin >> choice;

        // --------- RANGE SEARCH -------------------
        if (choice == 1)
        {
            float low;
            float high;
            cout << "Enter Lower Range: ";
            cin >> low;
            cout << "Enter Upper Range: ";
            cin >> high;

            if (low > high)
            {
                cout << "Invalid range! Lower limit cannot be greater than upper limit.\n";
                return;
            }

            Node *temp = head;
            bool found = false;

            while (temp != nullptr)
            {
                if (temp->cgpa >= low && temp->cgpa <= high)
                {
                    cout << "Name: " << temp->Name
                         << " | Roll No: " << temp->rollNo
                         << " | CGPA: " << temp->cgpa << endl;
                    found = true;
                }
                temp = temp->next;
            }

            if (!found)
                cout << "No students found in this CGPA range.\n";
        }

        // -------EXACT CGPA SEARCH -------------------
        else if (choice == 2)
        {
            float targetGpa;
            cout << "Enter Exact CGPA: ";
            cin >> targetGpa;

            Node *temp = head;
            bool found = false;

            while (temp != nullptr)
            {
                if (temp->cgpa == targetGpa)
                {
                    cout << "Name: " << temp->Name
                         << " | Roll No: " << temp->rollNo
                         << " | CGPA: " << temp->cgpa << endl;
                    found = true;
                }
                temp = temp->next;
            }

            if (!found)
                cout << "No student found with this CGPA.\n";
        }

        else
        {
            cout << "Invalid choice!\n";
        }
    }

    // search by name

    void searchStudent_ByName()
    {
        string search_Name;
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, search_Name);
        /*       cin >> search_Name;*/

        bool found = false;

        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->Name == search_Name)
            {
                cout << "\nName: " << temp->Name
                     << "\nRoll No: " << temp->rollNo
                     << "\nCGPA: " << temp->cgpa
                     << "\nAttendance: " << temp->attendance << "%";
                //<< "\nFee status: " << temp->feeStatus << "\n";

                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No student found with this name." << endl;
        }
    }

    // search by roll#
    void searchStudent_ByRollno()
    {
        int search_roll;
        cout << "Enter Student Roll No: ";
        cin >> search_roll;
        cin.ignore();

        Node *temp = head;
        bool found = false;
        while (temp != nullptr)
        {
            if (temp->rollNo == search_roll)
            {
                cout << "\nRoll No: " << temp->rollNo
                     << "\nName: " << temp->Name
                     << "\nCGPA: " << temp->cgpa
                     << "\nAttendance: " << temp->attendance << "%";
                //<< "\nFee status: " << temp->feeStatus << "\n";
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No student found with Roll Number " << search_roll << endl;
        }
    }

    bool isRollExist(int r)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->rollNo == r)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void SortBy_RollNo()
    {
        int n = countstudents();
        if (n < 2)
            return;
        Node *temp;
        Node *current;

        for (int i = 0; i < n - 1; i++)
        {
            current = head;

            for (int j = 0; j < n - 1 - i; j++)
            {
                if (current->rollNo > current->next->rollNo)
                {

                    int tRoll = current->rollNo;
                    current->rollNo = current->next->rollNo;
                    current->next->rollNo = tRoll;

                    string tName = current->Name;
                    current->Name = current->next->Name;
                    current->next->Name = tName;

                    float tCgpa = current->cgpa;
                    current->cgpa = current->next->cgpa;
                    current->next->cgpa = tCgpa;

                    int tAttendance = current->attendance;
                    current->attendance = current->next->attendance;
                    current->next->attendance = tAttendance;
                }
                current = current->next;
            }
        }

        cout << "\nStudents sorted by Roll Number!\n";
    }
};

// ---------------- MAIN OUTSIDE CLASS ------------------

int main()
{
    StudentList obj;
    // Node* head = nullptr;

    int id;

    while (true)
    {
        cout << "\n===== Student Record Management System =====";
        cout << "\n1) Add Student";
        cout << "\n2) Display All Students";
        cout << "\n3) Update Student";
        cout << "\n4) Search Student by Name";
        cout << "\n5) Search Student by Roll No";
        cout << "\n6) Search Student by CGPA";
        cout << "\n7) Sort by Roll No";
        cout << "\n8) Show Attendance\n";
        cout << "-----------------------------------------------------------------\n";

        cout << "Enter id: ";
        cin >> id;

        if (id == 1)
        {
            obj.insertStudent();
        }
        else if (id == 2)
        {
            obj.displayStudents(obj.head);
        }
        else if (id == 4)
        {
            obj.searchStudent_ByName();
        }
        else if (id == 5)
        {
            obj.searchStudent_ByRollno();
        }
        else if (id == 6)
        {
            obj.searchStudent_ByGPA();
        }
        else if (id == 7)
        {
            obj.SortBy_RollNo();
            obj.displayStudents(obj.head);
        }
        else if (id == 8)
        {
            obj.showAttendance();
        }
    }
}