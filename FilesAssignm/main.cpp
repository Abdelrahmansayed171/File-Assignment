#include <iostream>
#include <bits/stdc++.h>
#include<strstream>
using namespace std;
const string emp= "Employee.txt", dep = "Department.txt", Emp_PIndex = "PIndex_Emp.txt" , Dep_PIndex = "PIndex_Dep.txt";
int EmpNum = 0,highBOff;
fstream empl(emp,ios::app|ios::in);
fstream depa(dep,ios::app|ios::in);
fstream prim(Emp_PIndex, ios::app|ios::in);
fstream primdep(Dep_PIndex, ios::app|ios::in);
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
    static int toInt(char arr[],int sizee){
        vector <int> v;
        int tmp = 0;
        for(int i =0; i < sizee;i++){
            if(arr[i]!=' '){
                v.push_back((int)arr[i]-'0');
            }
            else{
                break;
            }
        }
        int multi = 1;
        for(int i = v.size()-1;i>= 0;i--){
            tmp += v[i]*multi;
            multi *=10;
        }
        return tmp;
    }
    static void Format(char s[],int len){
        int written = strlen(s);
        for(int i =written;i < len;i++){
            s[i] = ' ';
        }
    }
    static void readStudent(fstream & file)
    {
        char indicator[4];
        file.read(indicator,4);
        int length = toInt(indicator,4);
        char record[length];
        file.read(record,length);
        cout << length <<endl;
        for(int i = 0;i <length;i++){
            cout << record[i];
        }
        istrstream strbuff(record);
    }
};
class DepPIndex: public Entity{
public:
    char Dept_ID[30];
    int byteOff;
    void writeindex(fstream & file,char* d,int byteOff){
        file.write(d, 12);
        string lol = Entity::toChar(byteOff);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        Entity::Format(char_array,sizeof(byteOff));
        file.write(char_array, sizeof(byteOff));
    }
};
class EmpPIndex: public Entity{
public:
    char Employee_ID[13];
    int byteOff;
    void writeindex(fstream & file,char* e,int byteOff){
        file.write(e, 12);
        string lol = Entity::toChar(byteOff);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        Entity::Format(char_array,sizeof(byteOff));
        file.write(char_array, sizeof(byteOff));
    }
//    int searchID(fstream & file,string ID){
//        int numRec = EmpNum;
//        int byteOff=-1;
//        int low = 4, mid, high = highBOff;
//
//        while (low <= high)
//        {
//            mid = (low + high) / 2;
//            if (ID < PrmIndxArray[mid].ID)
//                high = mid - 1;
//            else if (ID > PrmIndxArray[mid].ID)
//                low = mid + 1;
//            else{
//                byteOff= PrmIndxArray[mid].RRN;
//                break;
//            }
//        }
//        return byteOff;
//    }
};

class Employee: public Entity{
public:
    char Employee_ID[13];
    char Employee_Name[50];
    char Employee_Position[50];
    char Dept_ID[30];
    Employee(){
        EmpNum++;
    }
    void writeRecord(fstream & file,Employee &e){
        int employeeRecordLength, employeeIDLength, employeeNameLength ,employeePositionLength,deptidLength;
        employeeIDLength=strlen(e.Employee_ID);
        employeeNameLength=strlen(e.Employee_Name);
        employeePositionLength=strlen(e.Employee_Position);
        deptidLength=strlen(e.Dept_ID);
        employeeRecordLength=employeeIDLength+employeeNameLength+employeePositionLength+deptidLength+4;
        cout << employeeRecordLength <<endl;
        empl.seekp(0,ios::end);
        int byteOff = empl.tellp();
        highBOff = byteOff;
        string lol = e.toChar(employeeRecordLength);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        Entity::Format(char_array,sizeof(byteOff));
        file.write(char_array, sizeof(n));

        file.write(e.Employee_ID, employeeIDLength);
        file.write("|", 1);
        file.write(e.Employee_Name, employeeNameLength);
        file.write("|", 1);
        file.write(e.Employee_Position, employeePositionLength);
        file.write("|", 1);
        file.write(e.Dept_ID, deptidLength);
        file.write("|", 1);
        Entity::Format(e.Employee_ID,13);
        EmpPIndex primwriter;
        primwriter.writeindex(prim,e.Employee_ID,byteOff);
    }
    static void deleteRecord(fstream & file,int ID){
        int byte_offset;
        int header_list=-1;
        int li;
        cin >> byte_offset;

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
        int DepartmentRecordLength, DepartmentIDLength, DepartmentNameLength ,DepartmentManegerLength;
        DepartmentIDLength=strlen(d.Dept_ID);
        DepartmentNameLength=strlen(d.Dept_Name);
        DepartmentManegerLength=strlen(d.Dept_manager);
        DepartmentRecordLength=DepartmentIDLength+DepartmentNameLength+DepartmentManegerLength+4;
        cout << DepartmentRecordLength <<endl;
        depa.seekp(0,ios::end);
        int byteOff = depa.tellp();
        string lol = d.toChar(DepartmentRecordLength);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        Entity::Format(char_array,sizeof(byteOff));
        file.write(char_array, sizeof(n));

        file.write(d.Dept_ID, DepartmentIDLength);
        file.write("|", 1);
        file.write(d.Dept_Name, DepartmentNameLength);
        file.write("|", 1);
        file.write(d.Dept_manager, DepartmentManegerLength);
        file.write("|", 1);

        Entity::Format(d.Dept_ID,30);
        DepPIndex primwriter;
        primwriter.writeindex(primdep,d.Dept_ID,byteOff);
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
    Entity::readStudent(empl);
}
