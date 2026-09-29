// Test driver
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "unsorted.h"

using namespace std;

void DisplayList(UnsortedType& list);
void DisplayState(UnsortedType& list, string label);

int main()
{
    srand(time(0));

    UnsortedType list;

    // Random point between insertions 1 and 49.
    int randomPoint = rand() % 49 + 1;

    // Point 1: Empty list
    DisplayState(list, "POINT 1: EMPTY LIST");

    // Fill the list with 50 random integers from 1 through 100.
    for (int i = 1; i <= 50; i++)
    {
        ItemType item;
        int randomValue = rand() % 100 + 1;

        item.Initialize(randomValue);
        list.PutItem(item);

        // Point 2: Random point during construction
        if (i == randomPoint)
        {
            cout << "\nRandom checkpoint occurred after "
                 << i << " insertions." << endl;

            DisplayState(list, "POINT 2: RANDOM POINT");
        }
    }

    // Point 3: All 50 integers inserted
    DisplayState(list, "POINT 3: 50 INTEGERS");

    return 0;
}

void DisplayList(UnsortedType& list)
{
    int length = list.GetLength();

    if (length == 0)
    {
        cout << "List is empty." << endl;
        return;
    }

    list.ResetList();

    for (int i = 0; i < length; i++)
    {
        ItemType item = list.GetNextItem();
        item.Print(cout);
        cout << " ";
    }

    cout << endl;
}

void DisplayState(UnsortedType& list, string label)
{
    cout << "\n========================================" << endl;
    cout << label << endl;
    cout << "========================================" << endl;

    cout << "Length: " << list.GetLength() << endl;

    cout << "List: ";
    DisplayList(list);

    if (list.GetLength() == 0)
    {
        cout << "Head: N/A (list is empty)" << endl;
        cout << "Tail: N/A (list is empty)" << endl;
        return;
    }

    ItemType head = list.Head();

    cout << "Head: ";
    head.Print(cout);
    cout << endl;

    UnsortedType tail = list.Tail();

    cout << "Tail: ";
    DisplayList(tail);
}