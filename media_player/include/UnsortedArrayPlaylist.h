#ifndef UNSORTED_ARRAY_PLAYLIST_H
#define UNSORTED_ARRAY_PLAYLIST_H
#include "Song.h"
#include <vector>
#include <string>
class UnsortedArrayPlaylist {
    std::vector<Song> songs;
public:
    void addSong(const Song& song) { songs.push_back(song); } // amortized O(1)
    bool removeSong(const std::string& title) { // O(n)
        for (auto it = songs.begin(); it != songs.end(); ++it)
            if (it->title == title) { songs.erase(it); return true; }
        return false;
    }
    const Song* getSong(int i) const { // O(1)
        return i >= 0 && static_cast<size_t>(i) < songs.size() ? &songs[i] : nullptr;
    }
    std::vector<Song> getSongs() const { return songs; } // O(n)
    int Length() const { return static_cast<int>(songs.size()); } // O(1)
};
#endif
