// Student name:
// Student ID  :

/*
 Submission deadline : Wed., 10 Oct 2018, 11:59 pm
 
 Implement the functions compare_MajorName(), sort_MajorName() and binSearch_MajorName().
 
 Upload your .cpp file to Canvas.
 Late submission or submission by other means are not accepted.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct studentRec
{
    string name;
    int sid;
    string major;
    int cohort;
};

ostream& operator<<(ostream& os, const studentRec& r)
{
    os << r.name << ", " << r.sid << ", " << r.major << ", " << r.cohort;
    return os;
}

int compare_MajorName(const studentRec& s1, const studentRec& s2)
{
    // compare s1 with s2 based on major and then name
    // return a negative value if s1 < s2
    // return zero             if s1 == s2
    // return a positive value if s1 > s2
    
    // To compare 2 string objects, you can use the compare() function in class string,
    // or you can use the relational operators <, >, ==.
    if (s1.major.compare(s2.major) != 0) {
        return s1.major.compare(s2.major);
    }else {
        return s1.name.compare(s2.name);
    }
}

void sort_MajorName(studentRec *list, int n)
{
    // sort the list by major and then name.
    
    // Write your own codes. Use any sorting method that you know.
    // Implement your sorting function with the help of the compare_MajorName() function.
    
    // Selection sort
    for(int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (compare_MajorName(list[minIndex], list[j]) > 0) {
                minIndex = j;
            }
        }
        studentRec temp = list[minIndex];
        list[minIndex] = list[i];
        list[i] = temp;
    }
}

int binSearch_MajorName(const studentRec *list, int n, const string& major, const string& name)
{
    // Precondition: The list is sorted by major and then name.
    
    // Use binary search to find the student by (major, name).
    // Implement your search function with the help of the compare_MajorName() function.
    
    int low = 0;
    int high = n - 1;
    int loc = -1;
    
    studentRec target;
    target.name = name;
    target.major = major;
    
    while (low <= high && loc == -1) {
        int mid = (low + high) / 2;
        if (compare_MajorName(list[mid], target) < 0) {
            low = mid + 1;
        }else if (compare_MajorName(list[mid], target) > 0) {
            high = mid - 1;
        }else {
            loc = mid;
        }
    }
    
    return loc;
}


// functions prepared for you

void readDataFile(const string& filename, studentRec*& list, int& n)
{
    // Parameter list and n are passed by reference.
    // This function is implemented for you.
    
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cout << "Cannot open data file " << filename << endl;
        system("pause");
        exit(1);
    }
    
    string line;
    getline(inFile, line);  // read in 1 line from inFile
    n = stoi(line);         // stoi : string_to_int conversion
    
    list = new studentRec[n];
    
    for (int i = 0; i < n; i++)
    {
        getline(inFile, line);
        
        int k = line.find(","); // find 1st occurrence of ","
        list[i]. name = line.substr(0, k);  // substr(startIndex, length) : substring
        
        int j = k + 1;
        k = line.find(",", j); // find next occurrence of "," start from index j
        list[i].sid = stoi(line.substr(j, k-j));
        
        j = k + 1;
        k = line.find(",", j);
        list[i].major = line.substr(j, k-j);
        list[i].cohort = stoi(line.substr(k+1));
    }
    inFile.close();
}

int main()
{
    string filename = "Tut_04_data.txt";
    studentRec* list;
    int n;
    
    readDataFile(filename, list, n);
    
    sort_MajorName(list, n);
    
    // print the list
    for (int i = 0; i < n; i++)
        cout << setw(3) << i << " : " << list[i] << endl;
    
    
    cout << "\n---------------------------------------------------\n";
    cout << "Test binary search function:\n\n";
    
    string majors[] = {"CDE", "ECE", "INFE", "EXCG"};
    
    for (int i = 0; i < 15; i++)
    {
        int k = rand() % n;
        string name = list[k].name;
        int j = rand() % 4;
        
        int loc = binSearch_MajorName(list, n, majors[j], name);
        
        if (loc < 0)
            cout << "(" << majors[j] << ", " << name << ") is not found\n\n";
        else
            cout << "(" << majors[j] << ", " << name << ") is found at index " << loc << endl << endl;
    }
    
    system("pause");
    return 0;
}
