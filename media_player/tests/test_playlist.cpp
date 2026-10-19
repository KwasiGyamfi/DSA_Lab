
#include <catch2/catch_test_macros.hpp>
#include "Playlist.h"
#include "SortedLinkedList.h"
#include "CircularLinkedList.h"
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <cstdio>

using namespace std;

TEST_CASE("A new playlist starts empty", "[playlist]")
{
    Playlist playlist;

    REQUIRE(playlist.IsEmpty());
    REQUIRE(playlist.Length() == 0);
    REQUIRE(playlist.getCurrentSong() == nullptr);
}

TEST_CASE("Songs can be inserted and navigated", "[playlist]")
{
    Playlist playlist;

    playlist.addSong(Song("A", "Artist A", 120, "a.mp3"));
    playlist.addSong(Song("B", "Artist B", 140, "b.mp3"));
    playlist.addSong(Song("C", "Artist C", 160, "c.mp3"));

    REQUIRE(playlist.Length() == 3);
    REQUIRE(playlist.getCurrentSong()->title == "A");

    playlist.nextSong();
    REQUIRE(playlist.getCurrentSong()->title == "C");

    playlist.previousSong();
    REQUIRE(playlist.getCurrentSong()->title == "A");
}

TEST_CASE("Removing a song updates the playlist", "[playlist]")
{
    Playlist playlist;

    playlist.addSong(Song("A", "Artist A", 120, "a.mp3"));
    playlist.addSong(Song("B", "Artist B", 140, "b.mp3"));

    playlist.removeSong("B");

    REQUIRE(playlist.Length() == 1);
    REQUIRE(playlist.getCurrentSong()->title == "A");
}

TEST_CASE("Sorting orders songs alphabetically", "[playlist]")
{
    Playlist playlist;

    playlist.addSong(Song("Zebra", "Z", 120, "z.mp3"));
    playlist.addSong(Song("Apple", "A", 140, "a.mp3"));
    playlist.addSong(Song("Mango", "M", 160, "m.mp3"));

    playlist.sortByTitle();

    vector<Song> songs = playlist.getSongs();

    REQUIRE(songs.size() == 3);
    REQUIRE(songs[0].title == "Apple");
    REQUIRE(songs[1].title == "Mango");
    REQUIRE(songs[2].title == "Zebra");
}

TEST_CASE("Merging preserves the source playlist", "[playlist]")
{
    Playlist first;
    Playlist second;

    first.addSong(Song("A", "Artist A", 120, "a.mp3"));
    second.addSong(Song("B", "Artist B", 140, "b.mp3"));

    first.mergeFrom(second);

    REQUIRE(first.Length() == 2);
    REQUIRE(second.Length() == 1);

    vector<Song> songs = first.getSongs();

    REQUIRE(songs[0].title == "A");
    REQUIRE(songs[1].title == "B");
}

TEST_CASE("Sorted linked list maintains order", "[sorted]")
{
    SortedLinkedList sorted;

    sorted.Insert(new Song("Zebra", "Z", 120, "z.mp3"));
    sorted.Insert(new Song("Apple", "A", 140, "a.mp3"));
    sorted.Insert(new Song("Mango", "M", 160, "m.mp3"));

    REQUIRE(sorted.Length() == 3);

    Song apple("Apple", "A", 140, "a.mp3");
    Song mango("Mango", "M", 160, "m.mp3");

    REQUIRE(sorted.IsPresent(apple));
    REQUIRE(sorted.IsPresent(mango));
    REQUIRE(sorted.Remove(mango));
    REQUIRE(sorted.Length() == 2);
}

TEST_CASE("Circular linked list supports deletion and clearing", "[circular]")
{
    CircularLinkedList circular;

    circular.Insert(Song("A", "Artist A", 120, "a.mp3"));
    circular.Insert(Song("B", "Artist B", 140, "b.mp3"));
    circular.Insert(Song("C", "Artist C", 160, "c.mp3"));

    REQUIRE(circular.Length() == 3);
    REQUIRE(circular.IsPresent("B"));
    REQUIRE(circular.Remove("B"));
    REQUIRE_FALSE(circular.IsPresent("B"));
    REQUIRE(circular.Length() == 2);

    circular.Clear();

    REQUIRE(circular.Length() == 0);
}

TEST_CASE("Search for songs by title", "[playlist]")
{
    Playlist playlist;

    playlist.addSong(Song("Golden", "Artist A", 180, "golden.mp3"));
    playlist.addSong(Song("Sunrise", "Artist B", 200, "sunrise.mp3"));

    Song* found = playlist.searchSong("Golden");

    REQUIRE(found != nullptr);
    REQUIRE(found->artist == "Artist A");

    REQUIRE(playlist.searchSong("Missing") == nullptr);
}

TEST_CASE("Playlist exports songs to JSON", "[playlist]")
{
    Playlist playlist;

    playlist.addSong(Song("Golden", "Artist A", 180, "golden.mp3"));

    const string filename = "test_playlist_export.json";

    REQUIRE(playlist.exportToJson(filename));

    ifstream file(filename);
    REQUIRE(file.is_open());

    string contents(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    REQUIRE(contents.find("\"title\": \"Golden\"") != string::npos);
    REQUIRE(contents.find("\"duration\": 180") != string::npos);

    file.close();
    std::remove(filename.c_str());
}