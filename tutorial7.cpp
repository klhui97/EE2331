// Student name:
// Student ID  :

/*
 Submission deadline: Wed, 31 Oct 2018, 11:59 pm.
 
 This exercise is on doubly-linked list and design of template functions.
 
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
#include <string>

using namespace std;

template<class Type>
struct dnode  // doubly-linked list
{
    Type info;
    dnode<Type> *back, *next;
};

struct telRec
{
    string name;
    string tel;
};

//------------------------------------------------- print functions given to you

ostream& operator<<(ostream& os, const telRec& r)
{
    os << "(" << r.name << ", " << r.tel << ")" ;
    return os;
}

template<class Type>
void printList(const char *label, dnode<Type> *list)
{
    cout << label << "{ ";
    dnode<Type> *p = list;
    while (p != nullptr)
    {
        cout << p->info;
        if (p->next != nullptr)
            cout << ", ";
        
        p = p->next;
    }
    cout << " }" << endl << endl;
}

template<class Type>
void printList_reversed(const char *label, dnode<Type> *list)
{
    cout << label << "{ ";
    dnode<Type> *p = list;
    if (p != nullptr)
        while (p->next != nullptr)
            p = p->next;
    
    // p is pointing to the last node
    while (p != nullptr)
    {
        cout << p->info;
        if (p->back != nullptr)
            cout << ", ";
        
        p = p->back;
    }
    cout << " }" << endl << endl;
}

// ------------------------------------------------- functions to be implemented by you

template<class Type>
void insert_front(dnode<Type>*& list, const Type& r)
{
    // Insert r at the front of the list.
    
    // Implement this function.
    dnode<Type> *n = new dnode<Type>;
    n->info = r;
    n->next = nullptr;
    n->back = nullptr;
    if (list == nullptr) {
        list = n;
    }else {
        n->next = list;
        list->back = n;
    }
    list = n;
}

template<class Type>
dnode<Type>* search_moveToFront(dnode<Type>*& list, const Type& key, int (*compare)(const Type&, const Type&))
{
    // Search for the node holding the key based on the compare function.
    // If the matching node is found, move the node to the front of the list.
    // Return the address of the matching node if found, otherwise return nullptr.
    
    // Implement this function.
    dnode<Type> *p = list;
    while (p != nullptr && (*compare)(p->info, key) != 0)
        p = p->next;
    
    if (p != nullptr && p->back != nullptr)  // matching node is not the first node
    {
        p->back->next = p->next;
        if (p->next != nullptr)
            p->next->back = p->back;
        
        list->back = p;
        p->next = list;
        p->back = nullptr;
        list = p;
    }
    return p;
    
}

int compareName(const telRec& a, const telRec& b)
{
    return a.name.compare(b.name);
}

void test_searchTelByName(dnode<telRec>*& list, const string& name)
{
    // Use search_moveToFront() to find the tel of the given name.
    // Define your own compare function.
    
    dnode<telRec> *p = nullptr;
    
    
    // Your codes
    telRec t;
    t.name = name;
    p = search_moveToFront(list, t, compareName);
    
    if (p != nullptr)
        cout << "Tel of " << name << " is " << p->info.tel << endl;
    else
        cout << "Tel of " << name << " is not found" << endl;
    
    // print the list after performing the search function.
    printList("list : ", list);
}

//--------------------------------------------------------------------------------

int main()
{
    string names[] = {"John", "Eric", "Amy", "Mei", "Bill", "David"};
    string tels[] = {"92345671", "84563242", "95346542", "64338970", "91578543"};
    
    dnode<telRec>* list = nullptr;
    
    for (int i = 0; i < 5; i++)
    {
        telRec t;
        t.name = names[i];
        t.tel = tels[i];
        insert_front(list, t);
    }
    
    printList("list : ", list);
    
    test_searchTelByName(list, names[5]);
    test_searchTelByName(list, names[4]);
    test_searchTelByName(list, names[2]);
    test_searchTelByName(list, names[0]);
    
    printList_reversed("list (reversed): ", list);
    
    system("pause");
    return 0;
}
