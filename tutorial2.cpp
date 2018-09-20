// Student name:
// Student ID  :

/*
 Submission deadline: Wed, 26 Sept 2018, 11:59 pm
 
 
 Upload your .cpp file to Canvas.
 Put down your name and student ID at the top of your file.
 
 10% Marks will be deducted if
 - Submission without name or ID
 - Submission of other file types
 
 Late submission or submission by other means are not accepted.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int removeAll_unordered(int *a, int& n, const int *b, int m)
{
    // n = no. of elements in a[]
    // m = no. of elements in b[]
    // Elements in a[] are distinct, and elements in b[] are distinct.
    
    // Remove elements in a[] that can be found in b[].
    // Return the number of elements that are removed from a[].
    
    
    // Your codes
    int isFound = false;
    int originN = n;
    int i = 0;
    while (i < n) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                isFound = true;
                break;
            }
        }
        if (isFound) {
            a[i] = a[--n];
            isFound = false;
        }else {
            i++;
        }
    }
    
    return originN - n;
}

int removeAll_ordered(int *a, int& n, const int *b, int m)
{
    // n = no. of elements in a[]
    // m = no. of elements in b[]
    // Elements in a[] are distinct, and elements in b[] are distinct.
    // a[] and b[] are sorted in ascending order.
    
    // Remove elements in a[] that can be found in b[].
    // Return the number of elements that are removed from a[].
    
    // Do not define or create other array.
    // This task can be done in linear time, i.e. O(n+m) time.
    
    
    // Your codes
    int originN = n;
    int i = 0;
    int j = 0;
    int curI = 0;
    
    // curI = non-repeated index, once a[i] is < b[j] that means a[i] won't appear after b[j]
    // so a[i] is non-repeated value, we put it in curI and then increment curI and i by 1 to process next value
    // n is the remaining array size, if we found a[i] == b[j], the size will be decreased by 1, and we increment i and j by 1 to process next value beacuse a[] and b[] are distinct
    // when a[i] > b[j], unless a[i] >= b[j], otherwise we can't find any repeated value because it is sorted array. we just need to keep increment j until a[i] >= b[j]
    while (i < originN && j < m) {
        if (a[i] == b[j]) {
            n--;
            i++;
            j++;
        }else if (a[i] > b[j]) {
            j++;
        }else {
            a[curI++] = a[i++];
        }
    }
    
    return originN - n;
}

void printArray(const char *label, const int *a, int n)
{
    cout << label << " { ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
        if (i < n-1)
            cout << ", ";
    }
    cout << " }" << endl;
}

void part_1()  // unordered arrays with distinct elements
{
    int b[] = {6, 4, 3, 10, 9, 15, 7};
    int m = 7;
    
    cout << "Part-1: Unordered array" << endl;
    
    int a1[] = {5, 7, 14, 6, 2, 9, 11, 3};
    int n = 8;
    
    int count = removeAll_unordered(a1, n, b, m);
    printArray("a1[] = ", a1, n);
    cout << "No. of elements removed = " << count << endl << endl;
}

void part_2()  // ordered arrays with distinct elements
{
    int b[] = {2, 5, 6, 8, 9, 10, 12};
    int m = 7;
    
    cout << "Part-2: Ordered array" << endl;
    
    int a2[] = {2, 3, 4, 6, 8, 10, 11, 12};
    int n = 8;
    
    int count2 = removeAll_ordered(a2, n, b, m);
    printArray("a2[] = ", a2, n);
    cout << "No. of elements removed = " << count2 << endl << endl;
    
    int a3[] = {3, 4, 7, 13};
    int u = 4;
    
    int count3 = removeAll_ordered(a3, u, b, m);
    printArray("a3[] = ", a3, u);
    cout << "No. of elements removed = " << count3 << endl << endl;
    
    int a4[] = {5, 6, 9, 10};
    int v = 4;
    
    int count4 = removeAll_ordered(a4, v, b, m);
    printArray("a4[] = ", a4, v);
    cout << "No. of elements removed = " << count4 << endl << endl;
}

int main()
{
    part_1();
    part_2();
    
    system("pause");
    return 0;
}
