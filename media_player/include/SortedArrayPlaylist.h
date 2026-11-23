
#ifndef SORTED_ARRAY_PLAYLIST_H
#define SORTED_ARRAY_PLAYLIST_H

#include "Song.h"
#include <algorithm>
#include <string>
#include <vector>

class SortedArrayPlaylist
{
private:
    std::vector<Song> songs;

public:
    // O(n): Binary search plus shifting elements.
    void addSong(const Song& song)
    {
        auto position = std::lower_bound(
            songs.begin(),
            songs.end(),
            song
        );

        songs.insert(position, song);
    }

    // O(n): Search for and remove a matching title.
    bool removeSong(const std::string& title)
    {
        for (auto it = songs.begin(); it != songs.end(); ++it)
        {
            if (it->title == title)
            {
                songs.erase(it);
                return true;
            }
        }

        return false;
    }

    // O(log n): Binary search by title.
    const Song* searchSong(const std::string& title) const
    {
        auto position = std::lower_bound(
            songs.begin(),
            songs.end(),
            title,
            [](const Song& song, const std::string& value)
            {
                return song.title < value;
            }
        );

        if (position != songs.end() && position->title == title)
            return &(*position);

        return nullptr;
    }

    // O(1): Return the number of songs.
    int Length() const
    {
        return static_cast<int>(songs.size());
    }

    // O(1): Access a song by position.
    const Song* getSong(int index) const
    {
        if (index < 0 || index >= Length())
            return nullptr;

        return &songs[index];
    }

    // O(n): Return a copy of the playlist.
    std::vector<Song> getSongs() const
    {
        return songs;
    }

    // O(n + m): Merge two already-sorted playlists.
    void mergeSortedPlaylists(const SortedArrayPlaylist& other)
    {
        std::vector<Song> merged;

        merged.reserve(songs.size() + other.songs.size());

        std::merge(
            songs.begin(), songs.end(),
            other.songs.begin(), other.songs.end(),
            std::back_inserter(merged)
        );

        songs = std::move(merged);
    }

    // O((n + m) log(n + m)): Append and sort.
    void mergeWithUnsorted(const std::vector<Song>& incoming)
    {
        songs.insert(songs.end(), incoming.begin(), incoming.end());

        std::sort(songs.begin(), songs.end());
    }
};

#endif
