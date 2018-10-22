// Student name:
// Student ID  :

/*
 Submission deadline: Wed, 24 Oct 2018, 11:59 pm.
 
 This exercise is on singly-linked list.
 
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

// Template type is NOT used in this exercise
struct node
{
    int info;
    node *link;
};

int removeAll_unorder(node*& listA, node *listB)
{
    // Precondition: Elements in an input list are distinct.
    // Remove elements in listA that can be found in listB.
    // You need to use 2 pointer variables to traverse listA.
    
    // Return the number of elements that are removed from listA.
    node *a = listA;
    node *b = listB;
    int count = 0;
    
    while (b != NULL) {
        node *prev = NULL;
        while (a != NULL) {
            if (a->info == b->info) {
                if (prev == NULL) {
                    listA = a->link;
                }else {
                    prev->link = a->link;
                }
                count++;
            }else {
                prev = a;
            }
            a = a->link;
        }
        a = listA;
        b = b->link;
    }
    
    return count;  // dummy return statement
}

int removeAll_ordered(node*& listA, node *listB)
{
    // Preconditions: Elements in an input list are distinct,
    //                and are sorted in ascending order.
    
    // Remove elements in listA that can be found in listB.
    // You need to use 2 pointer variables to traverse listA.
    // Remaining elements in listA are ordered in ascending order.
    
    // Return the number of elements that are removed from listA.
    
    // Your algorithm should have linear time complexity.
    node *a = listA;
    node *b = listB;
    node *prev = NULL;
    int count = 0;
    
    while (a != NULL && b != NULL) {
        if (a->info == b->info) {
            if (prev == NULL) {
                listA = a->link;
            }else {
                prev->link = a->link;
            }
            count++;
            b = b->link;
        }else if (a->info > b->info) {
            b = b->link;
        }else {
            prev = a;
            a = a->link;
        }
    }
    
    
    return count; // dummy return statement
}

void printList(const char *label, node *list)
{
    cout << label << " { ";
    node *p = list;
    while (p != nullptr)
    {
        cout << p->info;
        if (p->link != nullptr)
            cout << ", ";
        
        p = p->link;
    }
    cout << " }" << endl;
}

node* createList(const int a[], int n)
{
    if (n == 0)
        return nullptr;
    
    node *p, *r;
    p = r = new node;
    p->info = a[0];
    for (int i = 1; i < n; i++)
    {
        r->link = new node;
        r = r->link;
        r->info = a[i];
    }
    r->link = nullptr;
    return p;
}

void part_1()  // unordered lists with distinct elements
{
    int b1[] = {6, 4, 3, 5, 9, 15, 7};
    int m1 = 7;
    
    cout << "Part-1: Unordered list" << endl << endl;
    
    int a1[] = {5, 7, 14, 6, 2, 9, 11, 3};
    int n1 = 8;
    
    node *listA1 = createList(a1, n1);
    node *listB1 = createList(b1, m1);
    
    int count1 = removeAll_unorder(listA1, listB1);
    printList("listA1 : ", listA1);
    cout << "No. of elements removed = " << count1 << endl << endl;
    
    int a2[] = {9, 4, 7};
    int n2 = 3;
    node *listA2 = createList(a2, n2);
    
    int count2 = removeAll_unorder(listA2, listB1);
    printList("listA2 : ", listA2);
    cout << "No. of elements removed = " << count2 << endl << endl;
    
}

void part_2()  // ordered lists with distinct elements
{
    int b2[] = {2, 5, 6, 8, 9, 10, 12, 15};
    int m2 = 8;
    
    cout << "--------------------------------------------\n";
    cout << "Part-2: Ordered list" << endl << endl;
    
    int a3[] = {2, 3, 4, 6, 8, 10, 11, 12};
    int n3 = 8;
    
    node *listA3 = createList(a3, n3);
    node *listB2 = createList(b2, m2);
    
    int count3 = removeAll_ordered(listA3, listB2);
    printList("listA3 : ", listA3);
    cout << "No. of elements removed = " << count3 << endl << endl;
    
    count3 = removeAll_ordered(listA3, nullptr);
    printList("listA3 : ", listA3);
    cout << "No. of elements removed = " << count3 << endl << endl;
    
    int a4[] = {6, 8, 9, 15};
    int n4 = 4;
    node *listA4 = createList(a4, n4);
    int count4 = removeAll_ordered(listA4, listB2);
    printList("listA3 : ", listA4);
    cout << "No. of elements removed = " << count4 << endl << endl;
}

int main()
{
    part_1();
    part_2();
    
    system("pause");
    return 0;
}
