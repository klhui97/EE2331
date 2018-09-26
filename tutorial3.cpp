// Student name:
// Student ID  :

/*
 Submission deadline : Wed, 3 Oct 2018, 11:59 pm
 
 Upload your .cpp file to Canvas.
 Late submission or submission by other means are not accepted.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct segment
{
    int value;
    int startIndex;
    int length;
};

int binarySearch_lastIndex(const int *a, int start, int pastEnd, int key)
{
    // Search for the key in a[start ... (pastEnd-1)], where a[] is sorted in ascending order.
    // Element at a[pastEnd] is excluded in the search operation.
    
    // If key is found within the search range, return the index of the last element
    // that is equal to key.
    // If key is not found, return a negative index value.
    
    
    // Your codes.
    int keyIndex = -1;
    int low = 0;
    int high = pastEnd - 1;
    int mid;
    
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] > key) {
            high = mid - 1;
        }else if (a[mid] < key) {
            low = mid + 1;
        }else {
            keyIndex = mid;
            low = mid + 1;
        }
    }
    
    return keyIndex; // dummy return statement
}

segment longestSegment(const int *a, int n)
{
    // Preconditions: a[] is sorted in ascending order and n > 0.
    
    // Use sequential processing to find the longest segment in a[].
    // A segment is a sequence of elements with the same value.
    
    segment max;
    max.length = 0;
    
    
    // Your codes
    int i = 0;
    while (i < n) {
        segment temp;
        temp.startIndex = i;
        temp.value = a[i];
        temp.length = 1;
        
        while (i + 1 < n && a[i + 1] == temp.value) {
            temp.length++;
            i++;
        }
        
        if (temp.length > max.length) {
            max = temp;
        }
        
        i++;
    }
    
    return max;
}

segment longestSegment_binSearch(const int *a, int n)
{
    // Preconditions: a[] is sorted in ascending order and n > 0
    
    // Use binarySearch_lastIndex() to speed up the process of finding the longest segment in a[].
    
    segment max;
    max.length = 0;
    
    
    // Your codes.
    int i = 0;
    while (i < n) {
        segment temp;
        temp.startIndex = i;
        temp.value = a[i];
        temp.length = 1;
        
        int lastIndex = binarySearch_lastIndex(a, i + 1, n, temp.value);
        if (lastIndex != -1) {
            temp.length = lastIndex - i + 1;
            i = lastIndex;
        }
        
        if (temp.length > max.length) {
            max = temp;
        }
        
        i++;
    }
    
    return max;
}

//-------------------------------------- supporting functions prepared for you

ostream& operator<<(ostream& os, const segment& s)
{
    os << "segment (value = " << s.value << ", startIndex = " << s.startIndex << ", length = " << s.length << ")";
    return os;
}

void printArray(const int d[], int n)
{
    cout << "array : n = " << n << endl;
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && i % 10 == 0)
            cout << endl;
        cout << setw(3) << d[i] << ", ";  // setw() : set the field width
    }
    cout << endl << endl;
}

int* genArray(int n)
{
    // Generate a sorted array with length n.
    
    int *a = new int[n];
    
    srand((unsigned)time(NULL));
    
    int value = rand() % 10;
    int i = 0;
    while (i < n)
    {
        value = value + rand() % 10;
        int len = rand() % 10000;  // segment length may be greater than 10000
        for (int j = i; j < i + len && j < n; j++)
            a[j] = value;
        
        i += len;
    }
    return a;
}

int main()
{
    // a[] is sorted in ascending order
    int a[] = {2, 2, 2, 2, 3, 3, 5, 5, 5, 5,
        5, 5, 6, 7, 7, 7, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 9, 9, 9};
    int n = 30;
    
    printArray(a, n);
    
    cout << "\nTest the binarySearch function:\n";
    for (int i = 1; i <= 10; i++)
        cout << "binarySearch_lastIndex(a, 0, n, " << i << ") = " << binarySearch_lastIndex(a, 0, n, i) << endl;
    cout << endl;
    
    cout << "-- Sequential search method--\n";
    cout << longestSegment(a, n) << endl;
    // Expected output:
    // segment (value = 8, startIndex = 16, length = 11)
    
    int m = 10000000;     // 10 million
    int *d = genArray(m); // d[] is sorted in ascending order
    
    clock_t begin, end;
    double elapsedTime;
    
    cout << "\nComputer generated array with length = " << m << endl;
    cout << "\n-- Sequential search method--\n";
    begin = clock();
    segment max1 = longestSegment(d, m);
    end = clock();
    cout << max1 << endl;
    elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;
    
    cout << "\n-- Binary search method--\n";
    begin = clock();
    segment max2 = longestSegment_binSearch(d, m) ;
    end = clock();
    cout << max2 << endl;
    elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;
    
    delete[] d;  // Return memory resource to system.
    
    system("pause");
    return 0;
}
