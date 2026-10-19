
#include <iostream>
#include "SortedLinkedList.h"
#include "CircularLinkedList.h"
#include "Song.h"

using namespace std;

int main()
{
    cout << "=== SORTED LINKED LIST ===\n";

    SortedLinkedList sorted;

    sorted.Insert(new Song("Zebra", "Artist Z", 200, "z.mp3"));
    sorted.Insert(new Song("Apple", "Artist A", 180, "a.mp3"));
    sorted.Insert(new Song("Mango", "Artist M", 190, "m.mp3"));

    cout << "Expected order: Apple, Mango, Zebra\n";
    cout << "Actual order:\n";
    sorted.ListItems();

    cout << "Length: " << sorted.Length() << endl;

    Song mango("Mango", "Artist M", 190, "m.mp3");

    cout << "Mango present: "
         << (sorted.IsPresent(mango) ? "PASS" : "FAIL")
         << endl;

    cout << "Remove Mango: "
         << (sorted.Remove(mango) ? "PASS" : "FAIL")
         << endl;

    cout << "After removal:\n";
    sorted.ListItems();

    cout << "\n=== CIRCULAR LINKED LIST ===\n";

    CircularLinkedList circular;

    circular.Insert(Song("Song A", "Artist 1", 180, "a.mp3"));
    circular.Insert(Song("Song B", "Artist 2", 200, "b.mp3"));
    circular.Insert(Song("Song C", "Artist 3", 160, "c.mp3"));

    cout << "Length: " << circular.Length() << endl;

    cout << "Circular contents:\n";
    circular.ListItems();

    cout << "Song B present: "
         << (circular.IsPresent("Song B") ? "PASS" : "FAIL")
         << endl;

    cout << "Remove Song B: "
         << (circular.Remove("Song B") ? "PASS" : "FAIL")
         << endl;

    cout << "After removal:\n";
    circular.ListItems();

    circular.Clear();

    cout << "Clear list: "
         << (circular.Length() == 0 ? "PASS" : "FAIL")
         << endl;




    return 0;
}
