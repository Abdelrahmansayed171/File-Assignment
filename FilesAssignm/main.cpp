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
    fstream file("assign.txt", ios::out );
//    while(true)
//    {
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
    cout << "10-)" <<" Exit "<<endl;
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

        //cout << employeeRecordLength;

        file.write((char*)&employeeRecordLength, sizeof(employeeRecordLength));



        file.write(e.Employee_ID, employeeIDLength);
        file.write("|", 1);

        file.write(e.Employee_Name, employeeNameLength);
        file.write("|", 1);

        file.write(e.Employee_Position, employeePositionLength);
        file.write("|", 1);

        file.write(e.Dept_ID, deptidLength);
        file.write("|", 1);


    }
    else if(choice == 2)
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


        file.write(d.Dept_ID, deptIDLength);
        file.write("|", 1);

        file.write(d.Dept_Name, deptNameLength);
        file.write("|", 1);

        file.write(d.Dept_manager, deptManagerLength);
        file.write("|", 1);


    }

    else if(choice==10)
    {
        file.close();
        return 0;
    }



    //}



    return 0;
}
