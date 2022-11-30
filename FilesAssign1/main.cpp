#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>

using namespace std;

struct Department
{
    char Dept_ID[30];
    char Dept_Name[30];
    char Dept_manager[30];
};

struct Employee
{
    char Employee_ID[13];
    char Employee_Name[50];
    char Employee_Position[50];
    char Dept_ID[30];
};



int main() {
    fstream file("assi.txt",ios::out | ios::in | ios::binary);
    while(true)
    {
        int choice;
        cout << "1-) " << " Add New Employee "<<endl;
        cout << "2-) " << " Add New Department "<<endl;
        cout << "3-) " << " Delete Employee by ID "<<endl;
        cout << "4-) " << " Delete Department by ID"<<endl;
        cout << "5-) " << " print Employee by ID"<<endl;
        cout << "6-) " << " print Employee by Department ID"<<endl;
        cout << "7-) " << " print Department by ID"<<endl;
        cout << "8-) " << " print Department by name"<<endl;
        cout << "9-) " << " Write a query "<<endl;
        cout << "10-) " << " Exit "<<endl;
        cin >> choice;
        if(choice==1)
        {
            Employee e;
            cin>>e.Employee_ID;
            cin>>e.Employee_Name;
            cin>>e.Employee_Position;
            cin>>e.Dept_ID;

            int employeeRecordLength, employeeIDLength, employeeNameLength ,employeePositionLength,deptidLength;
            employeeIDLength=strlen(e.Employee_ID);
            employeeNameLength=strlen(e.Employee_Name);
            employeePositionLength=strlen(e.Employee_Position);
            deptidLength=strlen(e.Dept_ID);

            employeeRecordLength=employeeIDLength+employeeNameLength+employeePositionLength+deptidLength;



            file.write((char*)&employeeRecordLength, sizeof(employeeRecordLength));

//            file.write((char*)&idlength, sizeof(idlength));
//            file.write(e.Employee_ID, idlength);
//
//            file.write((char*)&namelength, sizeof(namelength));
//            file.write(e.Employee_Name, namelength);
//
//            file.write((char*)&positionlength, sizeof(positionlength));
//            file.write(e.Employee_Position, positionlength);
//
//            file.write((char*)&deptidlength, sizeof(deptidlength));
//            file.write(e.Dept_ID, deptidlength);


        }
        if(choice == 2)
        {
            Department d;
            cin>>d.Dept_ID;
            cin>>d.Dept_Name;
            cin>>d.Dept_manager;


            int deptRecordLength, deptIDLength, deptNameLength ,deptManagerLength;
            deptIDLength=strlen(d.Dept_ID);
            deptNameLength=strlen(d.Dept_Name);
            deptManagerLength=strlen(d.Dept_manager);


            deptRecordLength=deptIDLength+deptNameLength+deptManagerLength;



            file.write((char*)&deptRecordLength, sizeof(deptRecordLength));

        }

        else if(choice==10)
        {
            return 0;
        }

    }



    return 0;
}
