
#include <iostream>
#include "Playlist.h"

using namespace std;

int main()
{
    Playlist playlist;

    cout << "1. Empty playlist: "
         << (playlist.IsEmpty() ? "PASS" : "FAIL") << endl;

    playlist.addSong(Song("Song A", "Artist 1", 180, "a.mp3"));
    playlist.addSong(Song("Song B", "Artist 2", 200, "b.mp3"));
    playlist.addSong(Song("Song C", "Artist 3", 150, "c.mp3"));

    cout << "2. Three songs inserted: "
         << (playlist.Length() == 3 ? "PASS" : "FAIL") << endl;

    Song* current = playlist.getCurrentSong();

    cout << "3. Current song: "
         << (current != nullptr ? current->title : "NONE") << endl;

    playlist.nextSong();
    current = playlist.getCurrentSong();

    cout << "4. After nextSong(): "
         << (current != nullptr ? current->title : "NONE") << endl;

    playlist.previousSong();
    current = playlist.getCurrentSong();

    cout << "5. After previousSong(): "
         << (current != nullptr ? current->title : "NONE") << endl;

    playlist.removeSong("Song B");

    cout << "6. After removing Song B: "
         << (playlist.Length() == 2 ? "PASS" : "FAIL") << endl;

    playlist.sortByTitle();

    cout << "7. Sorted playlist:" << endl;
    playlist.ListItems();

    cout << "8. Final length: " << playlist.Length() << endl;


cout << "\n=== PLAYLIST MERGE TEST ===\n";

Playlist other;

other.addSong(Song("Song E", "Artist 5", 210, "e.mp3"));
other.addSong(Song("Song D", "Artist 4", 190, "d.mp3"));

int originalLength = playlist.Length();

playlist.mergeFrom(other);

cout << "Merge length: "
     << (playlist.Length() == originalLength + 2
         ? "PASS" : "FAIL") << endl;

cout << "Source unchanged: "
     << (other.Length() == 2 ? "PASS" : "FAIL")
     << endl;

cout << "Merged playlist:\n";
playlist.ListItems();


    return 0;
}
