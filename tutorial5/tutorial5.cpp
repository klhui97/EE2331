// Student name:
// Student ID  :

/*
 Submission deadline: Wed., 17 Oct 2018, 11:59 pm
 
 Part-1 :
 Compare the speed of bubble sort, insertion sort and qsort.
 
 Part-2 :
 We shall use the data file of Tut-04.
 After reading in the student records, use qsort() to sort the list and
 use bsearch() to search the sorted list.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
struct studentRec
{
    string name;
    int sid;
    string major;
    int cohort;
};

void readDataFile(const string&, studentRec*&, int&);

// Part-1 : --------------------------- basic sorting algorithms

void bubbleSort(double *x, int n)
{
    // Implement the sorting function using the bubble sort algorithm.
    int switched = 1;
    for (int pass = 1; pass < n && switched; pass++) {
        switched = 0;
        for (int j = 0; j < n-pass; j++)
            if (x[j] > x[j+1])
            {
                double t = x[j];
                x[j] = x[j+1];
                x[j+1] = t;
                switched = 1;
            }
    }
    
}

void insertionSort(double *x, int n)
{
    // Implement the sorting function using the insertion sort algorithm.
    for (int i = 1; i < n; i++) {
        double t = x[i];
        int j;
        for (j = i-1; j >= 0 && x[j] > t; j--)
            x[j+1] = x[j];
        x[j+1] = t;
    }
    
}

int compareDouble(const void *a, const void *b)
{
    double *v1 = (double *)a;
    double *v2 = (double *)b;
    if (*v1 > *v2)
        return 1;
    else if (*v1 < *v2)
        return -1;
    else
        return 0;
}

void qsort_test(double *x, int n)
{
    // #### write your statements to sort array x[] using qsort().
    //      Define your own compare function.
    
    qsort(x, n, sizeof(double), compareDouble);
}

void part_1(int n)  // NO need to modify this function
{
    srand((unsigned)time(NULL));  // set the seed of the random number generator
    
    double *a = new double[n];  // create 3 arrays with identical contents
    double *b = new double[n];
    double *c = new double[n];
    
    for (int i = 0; i < n; i++)
        a[i] = b[i] = c[i] = rand() / 10000.0;
    
    clock_t begin, end;
    double elapsedTime;
    
    cout << "Bubble sort: size of array = " << n << endl;
    begin = clock();
    bubbleSort(a, n);
    end = clock();
    elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;
    
    // check the outputs of your sorting functions
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i+1])
        {
            cout << "\n*** 1 : Error detected in the outputs of your sorting function\n\n";
            system("pause");
            exit(1);
        }
    
    cout << "Insertion sort: size of array = " << n << endl;
    begin = clock();
    insertionSort(b, n);
    end = clock();
    elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;
    
    // check the outputs of your sorting functions
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i+1] || a[i] != b[i])
        {
            cout << "\n*** 2 : Error detected in the outputs of your sorting function\n\n";
            system("pause");
            exit(1);
        }
    
    cout << "qsort: size of array = " << n << endl;
    
    begin = clock();
    qsort_test(c, n);
    end = clock();
    elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;
    
    // check the outputs of your sorting functions
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i+1] || a[i] != b[i] || a[i] != c[i])
        {
            cout << "\n*** 3 : Error detected in the outputs of your sorting function\n\n";
            system("pause");
            exit(1);
        }
    
    delete[] a;
    delete[] b;
    delete[] c;
}

// Part-2 ---------------------------- qsort and bsearch with multi-field struct

ostream& operator<<(ostream& os, const studentRec& r)
{
    os << r.name << ", " << r.sid << ", " << r.major << ", " << r.cohort;
    return os;
}

int compareStudent(const void *a, const void *b)
{
    studentRec *s1 = (studentRec *)a;
    studentRec *s2 = (studentRec *)b;
    
    if (s1->major.compare(s2->major) != 0)
        return s1->major.compare(s2->major);
    return s1->name.compare(s2->name);
}

void part_2()  // add your statements to this function to perform sorting and searching
{
    string filename = "Tut_04_data.txt";
    studentRec* list;
    int n;
    
    readDataFile(filename, list, n);
    
    cout << "\n-------------------------------------------------------\n";
    cout << "part-2: qsort and bsearch with multi-field struct\n\n";
    
    // ### Use qsort to sort the list by major-name.
    //     Define your compare function required by qsort.
    qsort(list, n, sizeof(studentRec), compareStudent);
    
    // print the list
    for (int i = 0; i < n; i++)
        cout << setw(3) << i << " : " << list[i] << endl;
    
    // Test the bsearch function
    cout << "\nTest your usage of bsearch:\n";
    
    string majors[] = {"CDE", "ECE", "INFE", "EXCG"};
    for (int i = 0; i < 15; i++)
    {
        int k = rand() % n;
        int j = rand() % 4;
        
        string& name = list[k].name;  // reference variables
        string& major = majors[j];
        
        int loc = -1;
        
        // ### Use bsearch to search the list for the given (major, name).
        //     Determine the loc (index) of the record in the array if it is found.
        studentRec r;
        r.major = major;
        r.name = name;
        
        studentRec *p = (studentRec *)bsearch(&r, list, n, sizeof(studentRec), compareStudent);
        if (p != nullptr)
            loc = p - list;
        
        if (loc < 0)
            cout << "(" << major << ", " << name << ") is not found\n\n";
        else
            cout << "(" << major << ", " << name << ") is found at index " << loc << endl << endl;
        
    }
    
    delete[] list;
}

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
    getline(inFile, line);
    n = stoi(line);
    
    list = new studentRec[n];
    
    for (int i = 0; i < n; i++)
    {
        getline(inFile, line);
        
        int k = line.find(",");
        list[i]. name = line.substr(0, k);
        
        int j = k + 1;
        k = line.find(",", j);
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
    part_1(50000);
    
    part_2();   // uncomment this statement after you have done part_1
    
    system("pause");
    return 0;
}
