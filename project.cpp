#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

class University
{
private:
    string RollNo, Name, Subject, Address;

public:
    University() : RollNo(""), Name(""), Subject(""), Address("") {}

    void setRollNo(string rollNo)
    {
        RollNo = rollNo;
    }

    void setName(string name)
    {
        Name = name;
    }

    void setSubject(string subject)
    {
        Subject = subject;
    }

    void setAddress(string address)
    {
        Address = address;
    }

    string getRollNo()
    {
        return RollNo;
    }

    string getName()
    {
        return Name;
    }

    string getSubject()
    {
        return Subject;
    }

    string getAddress()
    {
        return Address;
    }
};

void add(University student)
{
    string rollNo, name, subject, address;

    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;
    student.setRollNo(rollNo);

    cout << "\tEnter Name Of Student: ";
    cin >> name;
    student.setName(name);

    cout << "\tEnter Subject Of Student: ";
    cin >> subject;
    student.setSubject(subject);

    cout << "\tEnter Address Of Student: ";
    cin >> address;
    student.setAddress(address);

    ofstream out("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university.txt", ios::app);
    if (!out)
    {
        cout << "\tError: File Can't Open!" << endl;
    }

    else
    {
        out << "\t" << student.getRollNo() << " : " << student.getName() << " : " << student.getSubject()
            << " : " << student.getAddress() << endl;
    }
    out.close();
    cout << "\tStudent Added Successfuly!" << endl;
}

void search()
{
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream in("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university.txt");
    if (!in)
    {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line))
    {
        int data = line.find(rollNo);
        if (data != string::npos)
        {
            cout << "\t" << line << endl;
            found = true;
            break;  // Exit the loop once the student is found
        }
    }

    if (!found)
    {
        cout << "\tStudent Not Found!" << endl;
    }

    in.close();
}


void update(University student)
{
    string oldRollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> oldRollNo;

    ifstream infile("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university.txt");
    ofstream outfile("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university_temp.txt");
    if (!infile || !outfile)
    {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line))
    {
        int pos = line.find(oldRollNo);
        if (pos != string::npos)
        {
            // Extract existing details from the line
            size_t firstDelim = line.find(" : ");
            size_t secondDelim = line.find(" : ", firstDelim + 3);
            size_t thirdDelim = line.find(" : ", secondDelim + 3);

            string currentRollNo = line.substr(1, firstDelim - 1);
            string currentName = line.substr(firstDelim + 3, secondDelim - firstDelim - 3);
            string currentSubject = line.substr(secondDelim + 3, thirdDelim - secondDelim - 3);
            string currentAddress = line.substr(thirdDelim + 3);

            // Prompt for new details, allowing the user to skip fields
            string newRollNo, name, subject, address;

            cout << "\tEnter New RollNo (or press Enter to keep the same): ";
            cin.ignore();
            getline(cin, newRollNo);
            student.setRollNo(newRollNo.empty() ? currentRollNo : newRollNo);

            cout << "\tEnter New Name (or press Enter to keep the same): ";
            getline(cin, name);
            student.setName(name.empty() ? currentName : name);

            cout << "\tEnter New Subject (or press Enter to keep the same): ";
            getline(cin, subject);
            student.setSubject(subject.empty() ? currentSubject : subject);

            cout << "\tEnter New Address (or press Enter to keep the same): ";
            getline(cin, address);
            student.setAddress(address.empty() ? currentAddress : address);

            // Construct the new line with updated details
            line = "\t" + student.getRollNo() + " : " + student.getName() + " : " + student.getSubject() + " : " + student.getAddress();
            found = true;
        }
        outfile << line << endl;
    }

    if (!found)
    {
        cout << "\tStudent Not Found!" << endl;
    }
    else
    {
        cout << "\tData Updated!" << endl;
    }

    infile.close();
    outfile.close();

    // Replace the original file with the updated file
    remove("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university.txt");
    rename("C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university_temp.txt", "C:/Users/Sarthak Ralhan/OneDrive/Desktop/Project/university.txt");
}



int main()
{
    University student;

    bool exit = false;
    while (!exit)
    {
        system("cls");
        int val;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t1.Add Student." << endl;
        cout << "\t2.Search Student." << endl;
        cout << "\t3.Update Data Of Student." << endl;
        cout << "\t4.Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            add(student);
            Sleep(2000);
        }

        else if (val == 2)
        {
            system("cls");
            search();
            Sleep(6000);
        }

        else if (val == 3)
        {
            system("cls");
            update(student);
            Sleep(2000);
        }

        else if (val == 4)
        {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(2000);
        }
    }
}