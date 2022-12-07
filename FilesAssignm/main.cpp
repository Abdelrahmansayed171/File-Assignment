#include <iostream>
#include <bits/stdc++.h>
#include<strstream>
using namespace std;

const string emp= "Employee.txt", dep = "Department.txt", Emp_PIndex = "PIndex_Emp.txt" , Dep_PIndex = "PIndex_Dep.txt";

fstream empl(emp,ios::out|ios::in);
fstream depa(dep,ios::out|ios::in);
fstream prim(Emp_PIndex, ios::out|ios::in);
fstream primdep(Dep_PIndex, ios::out|ios::in);

int deleted;
char flag[1] = {'*'};
char deli[1] = {'|'};

int listHeader  = -1;
int depListHeader=-1;



string toChar(int s){
    string tmp = "";
    if(s == -1){
        tmp = "-1";
        return tmp;
    }
    while(true){
        tmp += s%10 + '0';
        s/=10;
        if(s == 0)break;
    }
    reverse(tmp.begin(),tmp.end());
    return tmp;
}



void Format(string &s,int len){
    while(s.length()<len){
        s+=" ";
    }
}



void headerWriter(fstream &file){
    string s = toChar(listHeader);
    Format(s,4);
    int tmp = file.tellp();
    file.seekp(0,ios::beg);
    file.write(s.c_str(),sizeof(int));
    file.seekp(tmp,ios::beg);
}
void deptheaderWriter(fstream &file){
    string s = toChar(depListHeader);
    Format(s,4);
    int tmp = file.tellp();
    file.seekp(0,ios::beg);
    file.write(s.c_str(),sizeof(int));
    file.seekp(tmp,ios::beg);
}

int toInt(char arr[],int sizee){
    if(arr[0] == '-'){
        return -1;
    }
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

void FormatArr(char s[],int len){
    int written = strlen(s);
    for(int i =written;i < len;i++){
        s[i] = ' ';
    }
}




struct PIndex
{
    int byteOff;
    string Employee_ID;

};
struct DeptPIndex{
    int byteOff;
    string Dept_ID;
};

vector <PIndex> PrimeIndexes;
vector <DeptPIndex> depIndexs;



void quickSort(vector <PIndex>& PrmIndxArray, int left, int right)
{
    int i = left, j = right;
    PIndex tmp;
    string pivot = PrmIndxArray[(left + right) / 2].Employee_ID;
    while (i <= j) {
        while (PrmIndxArray[i].Employee_ID < pivot)
            i++;
        while (PrmIndxArray[j].Employee_ID > pivot)
            j--;
        if (i <= j) {
            tmp = PrmIndxArray[i];
            PrmIndxArray[i] = PrmIndxArray[j];
            PrmIndxArray[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        quickSort(PrmIndxArray, left, j);
    if (i < right)
        quickSort(PrmIndxArray, i, right);
}

void writeindex(fstream &file,vector <PIndex>& prims){
    quickSort(prims,0,prims.size()-1);
    file.seekp(0,ios::beg);
    for(int i = 0; i <prims.size();i++){
        file.write(prims[i].Employee_ID.c_str(), 13);
        string lol = toChar(prims[i].byteOff);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        FormatArr(char_array,sizeof(prims[i].byteOff));
        file.write(char_array, sizeof(prims[i].byteOff));
    }
}

int searchID(vector <PIndex>& PrmIndxArray,string ID)
{
    Format(ID,13);
    int RRN=-1;
    int low = 0, mid, high = PrmIndxArray.size()-1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ID < PrmIndxArray[mid].Employee_ID)
            high = mid - 1;
        else if (ID > PrmIndxArray[mid].Employee_ID)
            low = mid + 1;
        else{
            RRN= PrmIndxArray[mid].byteOff;
            deleted = mid;
            break;
        }
    }
    return RRN;
}
//---------------------------------------------------------------------------------------------
void DeptquickSort(vector <DeptPIndex>& PrmIndxArray, int left, int right)
{
    int i = left, j = right;
    DeptPIndex tmp;
    string pivot = PrmIndxArray[(left + right) / 2].Dept_ID;
    while (i <= j) {
        while (PrmIndxArray[i].Dept_ID < pivot)
            i++;
        while (PrmIndxArray[j].Dept_ID > pivot)
            j--;
        if (i <= j) {
            tmp = PrmIndxArray[i];
            PrmIndxArray[i] = PrmIndxArray[j];
            PrmIndxArray[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        DeptquickSort(PrmIndxArray, left, j);
    if (i < right)
        DeptquickSort(PrmIndxArray, i, right);
}

void Deptwriteindex(fstream &file,vector <DeptPIndex>& prims){
    DeptquickSort(prims,0,prims.size()-1);
    file.seekp(0,ios::beg);
    for(int i = 0; i <prims.size();i++){
        file.write(prims[i].Dept_ID.c_str(), 13);
        string lol = toChar(prims[i].byteOff);
        int n = lol.length();
        char char_array[n + 1];
        strcpy(char_array, lol.c_str());
        FormatArr(char_array,sizeof(prims[i].byteOff));
        file.write(char_array, sizeof(prims[i].byteOff));
    }
}

int DeptsearchID(vector <DeptPIndex>& depIndexs,string ID)
{
    Format(ID,13);
    int RRN=-1;
    int low = 0, mid, high = depIndexs.size()-1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ID < depIndexs[mid].Dept_ID)
            high = mid - 1;
        else if (ID > depIndexs[mid].Dept_ID)
            low = mid + 1;
        else{
            RRN= depIndexs[mid].byteOff;
            deleted = mid;
            break;
        }
    }
    return RRN;
}

//---------------------------------------------------------------------------------------------

void deleteID(fstream &file,vector <PIndex>& PrmIndxArray,string ID){
    int byteOff = searchID(PrmIndxArray,ID);
    file.seekp(byteOff,ios::beg);
    file.seekg(byteOff,ios::beg);
    char indicator[4];
    file.read(indicator,4);
    file.seekp(byteOff,ios::beg);
    file.seekg(byteOff,ios::beg);
    file.write(flag,1);
    string preIDX = toChar(listHeader);

    file.write(preIDX.c_str(),2);
    file.write(deli,1);
    file.write(indicator, 4);
    listHeader = byteOff;
    headerWriter(file);

    PrmIndxArray.erase(PrimeIndexes.begin()+ deleted);
    writeindex(prim,PrimeIndexes);
}


void DeptdeleteID(fstream &file,vector <DeptPIndex>& PrmIndxArray,string ID){
    int byteOff = DeptsearchID(PrmIndxArray,ID);
    file.seekp(byteOff,ios::beg);
    file.seekg(byteOff,ios::beg);
    char indicator[4];
    file.read(indicator,4);
    file.seekp(byteOff,ios::beg);
    file.seekg(byteOff,ios::beg);
    file.write(flag,1);
    string preIDX = toChar(depListHeader);

    file.write(preIDX.c_str(),2);
    file.write(deli,1);
    file.write(indicator, 4);
    depListHeader = byteOff;
    deptheaderWriter(file);

    PrmIndxArray.erase(depIndexs.begin()+ deleted);
    Deptwriteindex(primdep,depIndexs);
}

class Employee
{
public:
    string Employee_ID;
    string Employee_Name;
    string Employee_Position;
    string Dept_ID;



    void writeEmployee(fstream &file) {
        int employeeRecordLength, employeeIDLength, employeeNameLength, employeePositionLength, deptidLength;
        employeeIDLength = Employee_ID.size();
        employeeNameLength = Employee_Name.size();
        employeePositionLength = Employee_Position.size();
        deptidLength = Dept_ID.size();
        employeeRecordLength = employeeIDLength + employeeNameLength + employeePositionLength + deptidLength + 4;

        int tmp = listHeader;
        int pretemp;
        if (tmp != -1) {
            while (true){
                file.seekp(tmp + 1, ios::beg);
                file.seekg(tmp + 1, ios::beg);
                char prevByteOff[2];
                file.read(prevByteOff, 2);
                int posttemp = toInt(prevByteOff, 2);
                file.seekp(tmp + 4, ios::beg);
                file.seekg(tmp + 4, ios::beg);
                char indicator[4];
                file.read(indicator, 4);
                int length = toInt(indicator, 4);
                if (length >= employeeRecordLength) {
                    bool flag = false;
                    file.seekp(tmp, ios::beg);
                    file.seekg(tmp, ios::beg);
                    int current = file.tellp();
                    if (listHeader == current) {
                        flag = true;
                    }
                    if (posttemp == -1) {
                        file.seekp(pretemp + 1, ios::beg);
                        file.seekg(pretemp + 1, ios::beg);
                        string s = "-1";
                        file.write(s.c_str(), 2);
                        if (flag) {
                            listHeader = -1;
                            headerWriter(file);
                        }
                    }
                    else{
                        file.seekp(posttemp + 1, ios::beg);
                        file.seekg(posttemp + 1, ios::beg);
                        char newByteOff[2];
                        file.read(newByteOff, 2);
                        file.seekp(pretemp + 1, ios::beg);
                        file.seekg(pretemp + 1, ios::beg);
                        file.write(newByteOff, 2);
                        int x = toInt(newByteOff, 2);
                        if (flag) {
                            listHeader = x;
                            headerWriter(file);
                        }
                    }
                    file.seekp(tmp, ios::beg);
                    file.seekg(tmp, ios::beg);
                    int byteOff = empl.tellp();
                    string lol = toChar(employeeRecordLength);
                    int n = lol.length();
                    char char_array[n + 1];
                    strcpy(char_array, lol.c_str());
                    FormatArr(char_array, sizeof(byteOff));
                    file.write(char_array, sizeof(n));

                    file.write(Employee_ID.c_str(), employeeIDLength);
                    file.write("|", 1);
                    file.write(Employee_Name.c_str(), employeeNameLength);
                    file.write("|", 1);
                    file.write(Employee_Position.c_str(), employeePositionLength);
                    file.write("|", 1);
                    file.write(Dept_ID.c_str(), deptidLength);
                    file.write("|", 1);
                    Format(Employee_ID, 13);
                    PIndex idx;
                    idx.Employee_ID = Employee_ID;
                    idx.byteOff = byteOff;
                    PrimeIndexes.push_back(idx);
                    writeindex(prim, PrimeIndexes);
                    listHeader = tmp;
                    return;
                } else {
                    pretemp = tmp;
                    tmp = toInt(prevByteOff, 2);
                }
            }
        } else {
            int byteOff = empl.tellp();
            string lol = toChar(employeeRecordLength);
            int n = lol.length();
            char char_array[n + 1];
            strcpy(char_array, lol.c_str());
            FormatArr(char_array, sizeof(byteOff));
            file.write(char_array, sizeof(n));
            file.write(Employee_ID.c_str(), employeeIDLength);
            file.write("|", 1);
            file.write(Employee_Name.c_str(), employeeNameLength);
            file.write("|", 1);
            file.write(Employee_Position.c_str(), employeePositionLength);
            file.write("|", 1);
            file.write(Dept_ID.c_str(), deptidLength);
            file.write("|", 1);
            Format(Employee_ID, 13);
            PIndex idx;
            idx.Employee_ID = Employee_ID;
            idx.byteOff = byteOff;
            PrimeIndexes.push_back(idx);
            writeindex(prim, PrimeIndexes);
        }


    }



    string readEmployee(fstream & file)
    {
        char indicator[4];
        file.read(indicator,4);
        int length = toInt(indicator,4);
        char record[length];
        file.read(record,length);
        istrstream strbuff(record);
        string tmp = "";
        for(int i = 0;i < length;i++) tmp.push_back(record[i]);
        return tmp;
    }



    void PrintEmpbyID(fstream &file,vector <PIndex>& PrmIndxArray)
    {



        cout << endl << "Enter employee ID : ";
        cin >> Employee_ID;
        int rrn=searchID(PrmIndxArray,Employee_ID);
        file.seekg(rrn,ios::beg);
        string needed_rec=readEmployee(file);
        cout <<needed_rec<<endl;



    }

    friend istream & operator >> (istream &in,  Employee &e);
};


istream & operator >> (istream &in,  Employee &e){
    cout <<"Employee ID: ";
    cin>>e.Employee_ID;
    cout << endl;
    if(e.Employee_ID.size() == 0) return in;
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
///---------------------------------------------------------------------------------------------------------------------------
class Department
{
public:
    string Dept_ID;
    string Dept_Name;
    string Dept_Manager;




    void writeDept(fstream &file) {
        int DeptRecordLength, DeptIDLength, DeptNameLength, DeptManagerLength;
        DeptIDLength = Dept_ID.size();
        DeptNameLength = Dept_Name.size();
        DeptManagerLength = Dept_Manager.size();
        DeptRecordLength = DeptIDLength + DeptNameLength + DeptManagerLength + 4;

        int tmp = depListHeader;
        int pretemp;
        if (tmp != -1) {
            while (true){
                file.seekp(tmp + 1, ios::beg);
                file.seekg(tmp + 1, ios::beg);
                char prevByteOff[2];
                file.read(prevByteOff, 2);
                int posttemp = toInt(prevByteOff, 2);
                file.seekp(tmp + 4, ios::beg);
                file.seekg(tmp + 4, ios::beg);
                char indicator[4];
                file.read(indicator, 4);
                int length = toInt(indicator, 4);
                if (length >= DeptRecordLength) {
                    bool flag = false;
                    file.seekp(tmp, ios::beg);
                    file.seekg(tmp, ios::beg);
                    int current = file.tellp();
                    if (depListHeader == current) {
                        flag = true;
                    }
                    if (posttemp == -1) {
                        file.seekp(pretemp + 1, ios::beg);
                        file.seekg(pretemp + 1, ios::beg);
                        string s = "-1";
                        file.write(s.c_str(), 2);
                        if (flag) {
                            depListHeader = -1;
                            deptheaderWriter(file);
                        }
                    }
                    else{
                        file.seekp(posttemp + 1, ios::beg);
                        file.seekg(posttemp + 1, ios::beg);
                        char newByteOff[2];
                        file.read(newByteOff, 2);
                        file.seekp(pretemp + 1, ios::beg);
                        file.seekg(pretemp + 1, ios::beg);
                        file.write(newByteOff, 2);
                        int x = toInt(newByteOff, 2);
                        if (flag) {
                            depListHeader = x;
                            deptheaderWriter(file);
                        }
                    }
                    file.seekp(tmp, ios::beg);
                    file.seekg(tmp, ios::beg);
                    int byteOff = depa.tellp();
                    string lol = toChar(DeptRecordLength);
                    int n = lol.length();
                    char char_array[n + 1];
                    strcpy(char_array, lol.c_str());
                    FormatArr(char_array, sizeof(byteOff));
                    file.write(char_array, sizeof(n));

                    file.write(Dept_ID.c_str(), DeptIDLength);
                    file.write("|", 1);
                    file.write(Dept_Name.c_str(), DeptNameLength);
                    file.write("|", 1);
                    file.write(Dept_Manager.c_str(), DeptManagerLength);
                    file.write("|", 1);
                    Format(Dept_ID, 13);
                    DeptPIndex idx;
                    idx.Dept_ID = Dept_ID;
                    idx.byteOff = byteOff;
                    depIndexs.push_back(idx);
                    Deptwriteindex(primdep, depIndexs);
                    depListHeader = tmp;
                    return;
                } else {
                    pretemp = tmp;
                    tmp = toInt(prevByteOff, 2);
                }
            }
        } else {
            int byteOff = depa.tellp();
            string lol = toChar(DeptRecordLength);
            int n = lol.length();
            char char_array[n + 1];
            strcpy(char_array, lol.c_str());
            FormatArr(char_array, sizeof(byteOff));
            file.write(char_array, sizeof(n));
            file.write(Dept_ID.c_str(), DeptIDLength);
            file.write("|", 1);
            file.write(Dept_Name.c_str(), DeptNameLength);
            file.write("|", 1);
            file.write(Dept_Manager.c_str(), DeptManagerLength);
            file.write("|", 1);
            Format(Dept_ID, 13);
            DeptPIndex idx;
            idx.Dept_ID = Dept_ID;
            idx.byteOff = byteOff;
            depIndexs.push_back(idx);
            Deptwriteindex(primdep, depIndexs);
        }


    }



    string readDept(fstream & file)
    {
        char indicator[4];
        file.read(indicator,4);
        int length = toInt(indicator,4);
        char record[length];
        file.read(record,length);
        istrstream strbuff(record);
        string tmp = "";
        for(int i = 0;i < length;i++) tmp.push_back(record[i]);
        return tmp;
    }



    void PrintDeptbyID(fstream &file,vector <DeptPIndex>& PrmIndxArray)
    {

        cout << endl << "Enter Department ID : ";
        cin >> Dept_ID;
        int rrn=DeptsearchID(PrmIndxArray,Dept_ID);
        file.seekg(rrn,ios::beg);
        string needed_rec=readDept(file);
        cout <<needed_rec<<endl;
    }

    friend istream & operator >> (istream &in,  Department &d);
};


istream & operator >> (istream &in,  Department &d){
    cout <<"Department ID: ";
    cin>>d.Dept_ID;
    cout << endl;
    if(d.Dept_ID.size() == 0) return in;
    cout <<"Department Name: ";
    cin>>d.Dept_Name;
    cout << endl;
    cout <<"Department Manager: ";
    cin>>d.Dept_Manager;
    cout <<endl;
    return in;
}

int main(int argc, const char * argv[])
{
    string s = "-1  ";
    empl.write(s.c_str(),sizeof(int));
    depa.write(s.c_str(),sizeof(int));



//
//    Employee e,b;
//    cin >> e;
//    e.writeEmployee(empl);
////  deleteID(empl,PrimeIndexes,"1");
//    cin >> b;
//    b.writeEmployee(empl);
//    b.PrintEmpbyID(empl,PrimeIndexes);



    Department d,g;
    cin>>d;
    d.writeDept(depa);
    cin>>g;
    g.writeDept(depa);
    g.PrintDeptbyID(depa,depIndexs);


//    for (int i =0; i < PrimeIndexes.size();i++)cout << endl<< PrimeIndexes[i].Employee_ID<<' ';
    system("Pause");
    return 0;
}
