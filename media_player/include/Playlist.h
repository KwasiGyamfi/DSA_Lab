
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "UnsortedLinkedList.h"
#include "Song.h"
#include <string>
#include <vector>

class Playlist : public UnsortedLinkedList
{
private:
    int currentIndex;

public:
    Playlist();

    void addSong(const Song& song);
    void removeSong(const std::string& title);

    Song* getCurrentSong();
    void nextSong();
    void previousSong();

    // Select a song by its displayed playlist position.
    bool selectSong(int index);

    // Return all songs in playlist order.
    std::vector<Song> getSongs() const;

    // Sort songs alphabetically by title.
    void sortByTitle();

    // O(n + m): Append copies of another playlist's songs.
    void mergeFrom(const Playlist& other);

    // O(n): Search for a song by title.
    // Returns nullptr if the song does not exist.
    Song* searchSong(const std::string& title);
    // O(n): Export the playlist as a JSON file.
    bool exportToJson(const std::string& filename) const;
};

#endif
