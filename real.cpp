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
    float attendance;           // overall percentage
    int weeklyAttendance[8][3]; // 8 weeks x 3 days (Mon-Wed)
    Node *next = nullptr;

    Node(string n, int r, float c, float a)
    {
        Name = n;
        rollNo = r;
        cgpa = c;
        attendance = a;
        // initialize weekly attendance as -1 (not marked)
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 3; j++)
                weeklyAttendance[i][j] = -1;
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

    void insertStudent()
    {
        string name;
        int rollNo;
        float cgpa;

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

        float attendancePercent = 0; // start with 0% attendance

        Node *new_node = new Node(name, rollNo, cgpa, attendancePercent);

        if (head == nullptr)
            head = new_node;
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
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

    void updateStudent()
    {
        int roll;
        cout << "Enter Roll No to update: ";
        cin >> roll;

        Node *temp = head;
        while (temp != nullptr && temp->rollNo != roll)
            temp = temp->next;

        if (temp == nullptr)
        {
            cout << "Student not found.\n";
            return;
        }

        cout << "Enter new Name: ";
        cin.ignore();
        getline(cin, temp->Name);
        cout << "Enter new CGPA: ";
        cin >> temp->cgpa;
    }

    void searchStudent_ByGPA()
    {
        int choice;
        cout << "\n1) Search Student By CGPA Range";
        cout << "\n2) Search Student By Exact CGPA\n";
        cout << "Enter your choice" << " ";
        cin >> choice;

        if (choice == 1)
        {
            float low, high;
            cout << "Enter Lower Range: ";
            cin >> low;
            cout << "Enter Upper Range: ";
            cin >> high;

            if (low > high)
            {
                cout << "Invalid range!\n";
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
            cout << "Invalid choice!\n";
    }

    void searchStudent_ByName()
    {
        string search_Name;
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, search_Name);

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
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found)
            cout << "No student found with this name." << endl;
    }

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
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found)
            cout << "No student found with Roll Number " << search_roll << endl;
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
        Node *current;

        for (int i = 0; i < n - 1; i++)
        {
            current = head;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (current->rollNo > current->next->rollNo)
                {
                    swap(current->rollNo, current->next->rollNo);
                    swap(current->Name, current->next->Name);
                    swap(current->cgpa, current->next->cgpa);
                    swap(current->attendance, current->next->attendance);
                }
                current = current->next;
            }
        }
        cout << "\nStudents sorted by Roll Number!\n";
    }

    void deleteStudent_ByRollNo()
    {
        int roll;
        cout << "Enter Roll Number to delete: ";
        cin >> roll;
        if (head == nullptr)
        {
            cout << "No students to delete!\n";
            return;
        }
        if (head->rollNo == roll)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            cout << "Student deleted successfully!\n";
            return;
        }
        Node *current = head;
        while (current->next != nullptr)
        {
            if (current->next->rollNo == roll)
            {
                Node *temp = current->next;
                current->next = temp->next;
                delete temp;
                cout << "Student deleted successfully!\n";
                return;
            }
            current = current->next;
        }
        cout << "Student with Roll Number " << roll << " not found!\n";
    }

    // ================= NEW FUNCTIONS =================
    void markDailyAttendance()
    {
        int roll;
        cout << "Enter Student Roll Number: ";
        cin >> roll;

        Node *temp = head;
        while (temp && temp->rollNo != roll)
            temp = temp->next;

        if (!temp)
        {
            cout << "Student not found!\n";
            return;
        }

        int week, day, present;
        cout << "Enter Week Number (1-8): ";
        cin >> week;
        cout << "Enter Day (1=Monday,2=Tuesday,3=Wednesday): ";
        cin >> day;
        cout << "Enter Attendance (1=Present,0=Absent): ";
        cin >> present;

        string days[3] = {"Monday", "Tuesday", "Wednesday"};
        temp->weeklyAttendance[week - 1][day - 1] = present;

        // auto update %
        int total = 0, presentCount = 0;
        for (int w = 0; w < 8; w++)
            for (int d = 0; d < 3; d++)
                if (temp->weeklyAttendance[w][d] != -1)
                {
                    total++;
                    if (temp->weeklyAttendance[w][d] == 1)
                        presentCount++;
                }
        temp->attendance = total > 0 ? (presentCount * 100.0f) / total : 0;

        cout << "Attendance updated for " << temp->Name
             << " on " << days[day - 1] << " of Week " << week << ".\n";
        cout << "Updated Attendance: " << temp->attendance << "%\n";
    }

    void showTotalAttendance()
    {
        int roll;
        cout << "Enter Student Roll Number: ";
        cin >> roll;

        Node *temp = head;
        while (temp && temp->rollNo != roll)
            temp = temp->next;

        if (!temp)
        {
            cout << "Student not found!\n";
            return;
        }

        int total = 0, present = 0;
        for (int w = 0; w < 8; w++)
            for (int d = 0; d < 3; d++)
                if (temp->weeklyAttendance[w][d] != -1)
                {
                    total++;
                    if (temp->weeklyAttendance[w][d] == 1)
                        present++;
                }

        if (total == 0)
        {
            cout << "No attendance marked yet.\n";
            return;
        }

        float percent = (present * 100.0f) / total;
        cout << "Total Attendance: " << percent << "%\n";
    }
};

// ---------------- MAIN ------------------

int main()
{
    StudentList obj;
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
        cout << "\n8) Show Attendance";
        cout << "\n9) Delete Student";
        cout << "\n10) Mark Daily Attendance";
        cout << "\n11) Show Total Attendance";
        cout << "\n-------------------------------------------------\n";

        cout << "Enter id: ";
        cin >> id;

        switch (id)
        {
        case 1:
            obj.insertStudent();
            break;
        case 2:
            obj.displayStudents(obj.head);
            break;
        case 3:
            obj.updateStudent();
            obj.displayStudents(obj.head);
            break;
        case 4:
            obj.searchStudent_ByName();
            break;
        case 5:
            obj.searchStudent_ByRollno();
            break;
        case 6:
            obj.searchStudent_ByGPA();
            break;
        case 7:
            obj.SortBy_RollNo();
            obj.displayStudents(obj.head);
            break;
        case 8:
            obj.showAttendance();
            break;
        case 9:
            obj.deleteStudent_ByRollNo();
            break;
        case 10:
            obj.markDailyAttendance();
            break;
        case 11:
            obj.showTotalAttendance();
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    }
}