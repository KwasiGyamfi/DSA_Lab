#include <catch2/catch_test_macros.hpp>
#include "SortedSongPlaylist.h"
#include "SortedArrayPlaylist.h"
#include "UnsortedArrayPlaylist.h"
#include <vector>
#include <string>
using namespace std;
static Song makeSong(const string& title) { return Song(title,"Artist",10,title+".mp3"); }
TEST_CASE("Sorted linked merge preserves order and source", "[merge]") {
    SortedSongPlaylist a,b;
    a.addSong(makeSong("A")); a.addSong(makeSong("C"));
    b.addSong(makeSong("B")); b.addSong(makeSong("D"));
    a.mergeSortedPlaylists(b);
    auto songs=a.getSongs();
    REQUIRE(songs.size()==4);
    REQUIRE(songs[0].title=="A"); REQUIRE(songs[1].title=="B");
    REQUIRE(songs[2].title=="C"); REQUIRE(songs[3].title=="D");
    REQUIRE(b.getSongs().size()==2);
}
TEST_CASE("Sorted linked merge with unsorted stays sorted", "[merge]") {
    SortedSongPlaylist a; a.addSong(makeSong("B"));
    a.mergeWithUnsorted({makeSong("Z"),makeSong("A")});
    auto s=a.getSongs();
    REQUIRE(s.size()==3); REQUIRE(s[0].title=="A");
    REQUIRE(s[1].title=="B"); REQUIRE(s[2].title=="Z");
}
TEST_CASE("Sorted arrays merge and remain sorted", "[merge]") {
    SortedArrayPlaylist a,b;
    a.addSong(makeSong("C")); a.addSong(makeSong("A"));
    b.addSong(makeSong("D")); b.addSong(makeSong("B"));
    a.mergeSortedPlaylists(b);
    auto s=a.getSongs(); REQUIRE(s.size()==4);
    REQUIRE(s[0].title=="A"); REQUIRE(s[1].title=="B");
    REQUIRE(s[2].title=="C"); REQUIRE(s[3].title=="D");
    REQUIRE(b.Length()==2);
    a.mergeWithUnsorted({makeSong("AA"),makeSong("E")});
    s=a.getSongs(); REQUIRE(s.size()==6);
    REQUIRE(s[1].title=="AA"); REQUIRE(s[5].title=="E");
}
TEST_CASE("Unsorted array operations", "[array]") {
    UnsortedArrayPlaylist p;
    p.addSong(makeSong("B")); p.addSong(makeSong("A"));
    REQUIRE(p.Length()==2); REQUIRE(p.getSong(0)->title=="B");
    REQUIRE(p.removeSong("B")); REQUIRE(p.Length()==1);
    REQUIRE(p.getSong(-1)==nullptr);
}
