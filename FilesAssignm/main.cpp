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

int listHeader = -1;



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

vector <PIndex> PrimeIndexes;



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

class Employee
{
public:
    string Employee_ID;
    string Employee_Name;
    string Employee_Position;
    string Dept_ID;



    void writeEmployee(fstream &file, int tmp)
    {

        int employeeRecordLength, employeeIDLength, employeeNameLength ,employeePositionLength,deptidLength;
        employeeIDLength = Employee_ID.size();
        employeeNameLength = Employee_Name.size();
        employeePositionLength = Employee_Position.size();
        deptidLength = Dept_ID.size();
        employeeRecordLength = employeeIDLength + employeeNameLength + employeePositionLength + deptidLength + 4;

        if(tmp != -1){
            file.seekp(tmp+1,ios::beg);
            file.seekg(tmp+1,ios::beg);
            char prevByteOff[2];
            file.read(prevByteOff,2);
            file.seekp(tmp+4,ios::beg);
            file.seekg(tmp+4,ios::beg);
            char indicator[4];
            file.read(indicator,4);
            int length = toInt(indicator,4);
            if(length >= employeeRecordLength){
                file.seekp(tmp,ios::beg);
                file.seekg(tmp,ios::beg);
                int byteOff = empl.tellp();
                string lol = toChar(employeeRecordLength);
                int n = lol.length();
                char char_array[n + 1];
                strcpy(char_array, lol.c_str());
                FormatArr(char_array,sizeof(byteOff));
                file.write(char_array, sizeof(n));

                file.write(Employee_ID.c_str(), employeeIDLength);
                file.write("|", 1);
                file.write(Employee_Name.c_str(), employeeNameLength);
                file.write("|", 1);
                file.write(Employee_Position.c_str(), employeePositionLength);
                file.write("|", 1);
                file.write(Dept_ID.c_str(), deptidLength);
                file.write("|", 1);
                Format(Employee_ID,13);
                PIndex idx;
                idx.Employee_ID = Employee_ID;
                idx.byteOff     =  byteOff;
                PrimeIndexes.push_back(idx);
                writeindex(prim,PrimeIndexes);
                listHeader = tmp;
                cout << listHeader <<endl;
            }
            else{
                tmp = toInt(prevByteOff,2);
                writeEmployee(file,tmp);
            }
        }
        else{
            int byteOff = empl.tellp();
            string lol = toChar(employeeRecordLength);
            int n = lol.length();
            char char_array[n + 1];
            strcpy(char_array, lol.c_str());
            FormatArr(char_array,sizeof(byteOff));
            file.write(char_array, sizeof(n));

            file.write(Employee_ID.c_str(), employeeIDLength);
            file.write("|", 1);
            file.write(Employee_Name.c_str(), employeeNameLength);
            file.write("|", 1);
            file.write(Employee_Position.c_str(), employeePositionLength);
            file.write("|", 1);
            file.write(Dept_ID.c_str(), deptidLength);
            file.write("|", 1);
            Format(Employee_ID,13);
            PIndex idx;
            idx.Employee_ID = Employee_ID;
            idx.byteOff     =  byteOff;
            PrimeIndexes.push_back(idx);
            writeindex(prim,PrimeIndexes);
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



int main(int argc, const char * argv[])
{
    string s = "-1  ";
    empl.write(s.c_str(),sizeof(int));
    Employee e,b;
    cin >> e;
    e.writeEmployee(empl,listHeader);
    deleteID(empl,PrimeIndexes,"1");
    cin >> b;
    b.writeEmployee(empl,listHeader);
//    for (int i =0; i < PrimeIndexes.size();i++)cout << endl<< PrimeIndexes[i].Employee_ID<<' ';
    system("Pause");
    return 0;
}
