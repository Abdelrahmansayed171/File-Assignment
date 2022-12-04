#include <iostream>
#include <bits/stdc++.h>
#include<strstream>
using namespace std;

const string emp= "Employee.txt", dep = "Department.txt", Emp_PIndex = "PIndex_Emp.txt" , Dep_PIndex = "PIndex_Dep.txt";

fstream empl(emp,ios::out|ios::in);
fstream depa(dep,ios::out|ios::in);
fstream prim(Emp_PIndex, ios::out|ios::in);
fstream primdep(Dep_PIndex, ios::out|ios::in);



string toChar(int s){
    string tmp = "";
    while(true){
        tmp += s%10 + '0';
        s/=10;
        if(s == 0)break;
    }
    reverse(tmp.begin(),tmp.end());
    return tmp;
}


int toInt(char arr[],int sizee){
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


void Format(string &s,int len){
    while(s.length()<len){
        s+=" ";
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
            break;
        }
    }
    cout << RRN <<endl;
    return RRN;
}


class Employee
{
public:
    string Employee_ID;
    string Employee_Name;
    string Employee_Position;
    string Dept_ID;



    void writeEmployee(fstream &file)
    {
        int employeeRecordLength, employeeIDLength, employeeNameLength ,employeePositionLength,deptidLength;
        employeeIDLength = Employee_ID.size();
        employeeNameLength = Employee_Name.size();
        employeePositionLength = Employee_Position.size();
        deptidLength = Dept_ID.size();
        employeeRecordLength=employeeIDLength+employeeNameLength+employeePositionLength+deptidLength+4;
//        cout << employeeRecordLength <<endl;
//        empl.seekp(0,ios::end);
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

//struct SIndex
//{
//    string ID;
//    string Name;
//};
//
//Student GetStudent(int RNN,fstream &infile)
//{
//    Student student;
//    infile.seekg(RNN*40, ios::beg);
//    student.readStudent(infile);
//    return student;
//}
//int GetRecordRRN(PIndex PrmIndxArray[],int numRec,string ID)
//{
//    int RRN=-1;
//    int low = 0, mid, high = numRec-1;
//
//    while (low <= high)
//    {
//        mid = (low + high) / 2;
//        if (ID < PrmIndxArray[mid].ID)
//            high = mid - 1;
//        else if (ID > PrmIndxArray[mid].ID)
//            low = mid + 1;
//        else{
//            RRN= PrmIndxArray[mid].RRN;
//            break;
//        }
//    }
//    return RRN;
//}
//
//void WritePrimIndex(PIndex PrmIndxArray[],int numRec,fstream&outfile) {
//    for(int i =0;i<numRec;i++){
//        outfile.write((char*)&PrmIndxArray[i].RRN,sizeof(int));
//        outfile.write(PrmIndxArray[i].ID.c_str(),10);
//    }
//
//
//}
//
//void ReadPrimIndex(PIndex PrmIndxArray[],int numRec,fstream& inFile) {
//    for(int i =0;i<numRec;i++){
//        inFile.read((char*)&PrmIndxArray[i].RRN,sizeof(int));
//        char* tmp=new char[10];
//        inFile.read(tmp,10);
//        tmp[10]=0;
//        PrmIndxArray[i].ID=tmp;
//    }
//
//}
//
//
//void quickSort(PIndex PrmIndxArray[], int left, int right)
//{
//    int i = left, j = right;
//    PIndex tmp;
//    string pivot = PrmIndxArray[(left + right) / 2].ID;
//    while (i <= j) {
//        while (PrmIndxArray[i].ID < pivot)
//            i++;
//        while (PrmIndxArray[j].ID > pivot)
//            j--;
//        if (i <= j) {
//            tmp = PrmIndxArray[i];
//            PrmIndxArray[i] = PrmIndxArray[j];
//            PrmIndxArray[j] = tmp;
//            i++;
//            j--;
//        }
//    }
//    if (left < j)
//        quickSort(PrmIndxArray, left, j);
//    if (i < right)
//        quickSort(PrmIndxArray, i, right);
//}
//
//void Format(string &s,int len){
//    while(s.length()<len){
//        s+=" ";
//    }
//}
//int AddStudents(int numRec){
//    fstream file,PrimIndex;
//
//    file.open("file1.txt",ios::out);
//    PrimIndex.open("Primary.txt",ios::out);
//
//
//    PIndex *PrmIndxArray=new PIndex[numRec];
//    Student *students=new Student[numRec];
//
//    for(int i =0;i<numRec;i++){
//        Student tmp;
//        cout<<endl<<"Enter Student "<<i+1<<" ID (Max 10 Letters):";
//        cin>>tmp.ID;
//        Format(tmp.ID,10);
//        cout<<"Enter Student "<<i+1<<" Name (Max 10 Letters) :";
//        cin>>tmp.Name;
//        Format(tmp.Name,10);
//        cout<<"Enter Student "<<i+1<<" Address (Max 20 Letters) :";
//        cin>>tmp.Addr;
//        Format(tmp.Addr,20);
//
//        students[i]=tmp;
//
//        PrmIndxArray[i].RRN=i;
//        PrmIndxArray[i].ID=tmp.ID;
//
//        students[i].writeStudent(file);
//    }
//
//    quickSort(PrmIndxArray,0,numRec-1);
//    WritePrimIndex(PrmIndxArray,numRec,PrimIndex);
//
//    file.close();
//    PrimIndex.close();
//
//    return numRec;
//
//}
//
//void SearchById(int numRec){
//    fstream file,PrimIndex;
//
//    file.open("file1.txt",ios::in);
//    PrimIndex.open("Primary.txt",ios::in);
//
//
//    PIndex *PrmIndxArray=new PIndex[numRec];
//    Student *students=new Student[numRec];
//
//    ReadPrimIndex(PrmIndxArray,numRec,PrimIndex);
//
//
//    //printing index files
//    /*
//     cout<<"Primary index"<<endl;
//     for(int i =0;i<numRec;i++){
//     cout<<"RRN : "<<PrmIndxArray[i].RRN<<"  ID:"<<PrmIndxArray[i].ID<<endl;
//     }
//     */
//
//    string ID;
//    Student student;
//    int RRN;
//    cout<<endl<<"Enter Target Stundent ID : ";
//    cin>>ID;
//    Format(ID,10);
//
//    RRN= GetRecordRRN(PrmIndxArray,numRec,ID);
//    cout<<RRN<<endl;
//    student= GetStudent(RRN,file);
//    cout<<endl<<"Student ID : "<<student.ID<<"  Name: "<<student.Name<<"  Address: "<<student.Addr<<endl;
//
//    file.close();
//    PrimIndex.close();
//}

int main(int argc, const char * argv[])
{
    Employee e,d,b;
    cin >> e>>d>>b;
    e.writeEmployee(empl);
    d.writeEmployee(empl);
    b.writeEmployee(empl);
    int x = searchID(PrimeIndexes,"1");
    int y = searchID(PrimeIndexes,"2");
    int z = searchID(PrimeIndexes,"3");
    for (int i =0; i < PrimeIndexes.size();i++)cout << endl<< PrimeIndexes[i].Employee_ID<<' ';
    system("Pause");
    return 0;
}
