// Student name:
// Student ID  :

/*
 Submission deadline: Wed., 19 Sept. 2018, 11:59 pm.
 
 This exercise is on the conversion of IPv4 address from text (dot-decimal)
 format to binary, and vice versa.
 
 For example, IPv4 address 144.54.100.7 in binary format is 0x90366407
 
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
#include <sstream>

using namespace std;

unsigned text2Bin_IPv4(const char *a)
{
    unsigned v = 0;
    
    // Your codes.
    int i = 0, tempValue = 0;
    while (a[i] != '\0') {
        if (a[i] == '.') {
            v = v * 256 + tempValue;
            tempValue = 0;
        }else {
            tempValue *= 10;
            // char type - 48 can convert to int
            // In char world, (int)0 = 48, 1 = 49, 2 = 50, ...
            tempValue = tempValue + a[i] - 48;
        }
        i++;
    }
    v = v * 256 + tempValue;
    
    return v;
}


char* bin2Text_IPv4(unsigned v)
{
    char *a = new char[16];  // max len of IPv4 address is 16 chars, including '\0'
    a[0] = '\0';  // initialize a[] to an empty cstring
    
    // Your codes.
    int i = 0;
    int count = 0;
    unsigned base = 0x1000000;
    
    while (count < 4) {
        // Convert hex to decimal string
        stringstream ss;
        ss << dec << v / base;
        string stringValue = ss.str();
        int j = 0;
        while (stringValue[j] != '\0') {
            a[i++] = stringValue[j];
            j++;
        }
        
        // Only the first 3 number add dot
        if (count < 3) {
            a[i++] = '.';
        }
        
        count++;
        v = v % base;
        base /= 256;
    }
    a[i] = '\0';
    
    return a;
}

void printIPv4address_hex(unsigned v)
{
    unsigned base = 0x10000000;
    
    cout << "0x";
    
    for (int i = 0; i < 8; i++)
    {
        cout << hex << v / base;
        v = v % base;
        base /= 16;
    }
}

int main()
{
    char addr1[] = "0.1.10.0";     // dot-decimal format
    char addr2[] = "144.54.100.7";
    unsigned v1, v2;
    
    v1 = text2Bin_IPv4(addr1);  // expected result: v1 = 0x00010a00
    v2 = text2Bin_IPv4(addr2);  // expected result: v2 = 0x90366407
    
    cout << addr1 << " in binary format = ";
    printIPv4address_hex(v1);
    cout << endl;
    
    cout << addr2 << " in binary format = ";
    printIPv4address_hex(v2);
    cout << endl << endl;
    
    char *p1 = bin2Text_IPv4(v1);
    char *p2 = bin2Text_IPv4(v2);
    
    cout << "IPv4 address ";
    printIPv4address_hex(v1);
    cout << " in dot-decimal format is " << p1 << endl;
    
    cout << "IPv4 address ";
    printIPv4address_hex(v2);
    cout << " in dot-decimal format is " << p2 << endl;
    cout << endl;
    
    system("pause");
    return 0;
}
