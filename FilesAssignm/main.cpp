#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const string emp= "Employee.txt", dep = "Department.txt";
class Entity{
public:
    const static int maxRecordSize = 1000;
    static string toChar(int s){
        string tmp = "";
        while(true){
            tmp += s%10 + '0';
            s/=10;
            if(s == 0)break;
        }
        reverse(tmp.begin(),tmp.end());
        return tmp;
    }

};

class Employee: public Entity{
public:
    char Employee_ID[13];
    char Employee_Name[50];
    char Employee_Position[50];
    char Dept_ID[30];
    void writeRecord(fstream & file,Employee &e){
        int employeeRecordLength, employeeIDLength, employeeNameLength ,employeePositionLength,deptidLength;
        employeeIDLength=strlen(e.Employee_ID);
        employeeNameLength=strlen(e.Employee_Name);
        employeePositionLength=strlen(e.Employee_Position);
        deptidLength=strlen(e.Dept_ID);

        employeeRecordLength=employeeIDLength+employeeNameLength+employeePositionLength+deptidLength+4;
        cout << employeeRecordLength <<endl;
        string lol = e.toChar(employeeRecordLength);
        int n = lol.length();

        // declaring character array
        char char_array[n + 1];

        // copying the contents of the
        // string to char array
        strcpy(char_array, lol.c_str());

        file.write(char_array, n);



        file.write(e.Employee_ID, employeeIDLength);
        file.write("|", 1);

        file.write(e.Employee_Name, employeeNameLength);
        file.write("|", 1);

        file.write(e.Employee_Position, employeePositionLength);
        file.write("|", 1);

        file.write(e.Dept_ID, deptidLength);
        file.write("|", 1);
    }
    static void deleteRecord(fstream & file,int ID){
        int byte_offset;
        int header_list=-1;
        int li;
        cin >> byte_offset;
//
//        file.seekg(byte_offset, ios::beg);
//        file.get( (char)&li,sizeof (2));
//
//        cout << li<<endl;



        file.seekp(byte_offset, ios::beg);


//        file.put('');


        string loly = toChar(header_list);
        int n = loly.length();
        char char_array[n + 1];
        strcpy(char_array, loly.c_str());
        file.write(char_array, sizeof(header_list));

        file.write("|", 1);

//      file.write((char*)& li, sizeof(li));

//        file.write("|", 1);

        header_list=byte_offset;
    }
    friend istream & operator >> (istream &in,  Employee &e);

};
istream & operator >> (istream &in,  Employee &e){
    cout <<"Employee ID: ";
    cin>>e.Employee_ID;
    cout << endl;
    if(strlen(e.Employee_ID) == 0) return in;
    cout <<"Employee Name: ";
    cin>>e.Employee_Name;
    cout << endl;
    cout <<"Employee Position: ";
    cin>>e.Employee_Position;
    cout <<endl;
    cout <<"Department ID: ";
    cin>>e.Dept_ID;
    return in;
}
class Department :public Entity{
public:
    char Dept_ID[30];
    char Dept_Name[30];
    char Dept_manager[30];

    void writeRecord(fstream & file,Department &d){
        int deptRecordLength, deptIDLength, deptNameLength ,deptManagerLength;
        deptIDLength=strlen(d.Dept_ID);
        deptNameLength=strlen(d.Dept_Name);
        deptManagerLength=strlen(d.Dept_manager);


        deptRecordLength=deptIDLength+deptNameLength+deptManagerLength+3;
        string lol = toChar(deptRecordLength);
        int n = lol.length();

        // declaring character array
        char char_array[n + 1];

        // copying the contents of the
        // string to char array
        strcpy(char_array, lol.c_str());

        file.write(char_array, sizeof(deptRecordLength));


        file.write(d.Dept_ID, deptIDLength);
        file.write("|", 1);

        file.write(d.Dept_Name, deptNameLength);
        file.write("|", 1);

        file.write(d.Dept_manager, deptManagerLength);
        file.write("|", 1);
    }

    friend istream & operator >> (istream &in,  Department &dep);
};
istream & operator >> (istream &in,  Department &d){
    cout <<"Department ID: ";
    cin>>d.Dept_ID;
    cout << endl;
    if(strlen(d.Dept_ID) == 0) return in;
    cout <<"Department Name: ";
    cin>>d.Dept_Name;
    cout << endl;
    cout <<"Department Manger: ";
    cin>>d.Dept_manager;
    return in;
}
int main() {
    int choice;
    fstream empl(emp,ios::app);
    fstream depa(dep,ios::app);
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
        cin >> e;
        cout <<e.Employee_Name <<endl;
        e.writeRecord(empl,e);
    }
    else if(choice == 2)
    {
        Department d;
        cin >> d;
        cout <<d.Dept_Name <<endl;
        d.writeRecord(depa,d);
    }
    else if(choice ==3)
    {
        int empID;
        cin>>empID;
        Employee::deleteRecord(empl,empID);
    }
    else if(choice==10)
    {
        return 0;
    }
}
