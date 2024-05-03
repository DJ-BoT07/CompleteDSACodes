#include <iostream>
#include <fstream>
using namespace std;

class student
{
    string name;
    int rollno;

public:
    void add_info()
    {
        ofstream f;
        f.open("deva.txt", ios::app);
        if (!f)
            cout << "File creation failed";
        else
        {
            cout << "\nEnter the name: ";
            cin >> name;
            cout << "Enter the rollno: ";
            cin >> rollno;
            f << name << " " << rollno << endl;
            f.close();
            cout << "\nData added successfully.";
        }
    }

    void display()
    {
        ifstream f;
        f.open("deva.txt", ios::in);
        if (!f)
            cout << "No such file";
        else
        {
            cout << "\n*** Student Data ***\n";
            while (f >> name >> rollno)
            {
                cout << "Name: " << name << endl;
                cout << "Roll No: " << rollno << endl;
                cout << "\n";
            }
            f.close();
        }
    }

    void search()
    {
        ifstream f;
        f.open("deva.txt", ios::in);
        if (!f)
            cout << "No such file";
        else
        {
            string searchName;
            cout << "\nEnter the name to search: ";
            cin >> searchName;
            bool found = false;
            while (f >> name >> rollno)
            {
                if (name == searchName)
                {
                    cout << "\n*** Student Found ***\n";
                    cout << "Name: " << name << endl;
                    cout << "Roll No: " << rollno << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Student not found.";
            f.close();
        }
    }

    void deleteRecord()
    {
        ifstream f1;
        ofstream f2;
        f1.open("deva.txt", ios::in);
        if (!f1)
            cout << "No such file";
        else
        {
            string deleteName;
            cout << "\nEnter the name to delete: ";
            cin >> deleteName;
            bool deleted = false;
            f2.open("temp.txt", ios::out);
            while (f1 >> name >> rollno)
            {
                if (name != deleteName)
                    f2 << name << " " << rollno << endl;
                else
                    deleted = true;
            }
            f1.close();
            f2.close();
            remove("deva.txt");
            rename("temp.txt", "deva.txt");
            if (deleted)
                cout << "Record deleted successfully.";
            else
                cout << "Student not found.";
        }
    }
};

int main()
{
    int ch;
    student s;

    do
    {
        cout << "\n\t\t**** STUDENT DATA ****";
        cout << "\n\t\t1. Add information";
        cout << "\n\t\t2. Display information";
        cout << "\n\t\t3. Search record";
        cout << "\n\t\t4. Delete record";
        cout << "\n\t\t5. Exit";
        cout << "\n\t\tEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            s.add_info();
            break;
        case 2:
            s.display();
            break;
        case 3:
            s.search();
            break;
        case 4:
            s.deleteRecord();
            break;
        case 5:
            exit(0);
        }
    } while (ch != 5);

    return 0;
}
