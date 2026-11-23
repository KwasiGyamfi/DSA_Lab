#ifndef SORTED_SONG_PLAYLIST_H
#define SORTED_SONG_PLAYLIST_H
#include "SortedLinkedList.h"
#include "Song.h"
#include <vector>
#include <string>

// Sorted linked implementation. Nodes and song objects are privately owned.
class SortedSongPlaylist : public SortedLinkedList {
public:
    std::vector<Song> getSongs() const {
        std::vector<Song> result;
        for (Node* cur = listData; cur != nullptr; cur = cur->next) {
            const Song* s = dynamic_cast<const Song*>(cur->item);
            if (s) result.push_back(*s);
        }
        return result;
    }
    void addSong(const Song& s) { Insert(new Song(s)); }

    // O(n+m) time, O(n+m) additional space for copied songs/nodes.
    // Sorted inputs are traversed simultaneously and merged into a new list.
    void mergeSortedPlaylists(const SortedSongPlaylist& other) {
        auto left = getSongs();
        auto right = other.getSongs(); // snapshots also make self-merge safe
        Clear();
        size_t i = 0, j = 0;
        // Inserting sorted values into SortedLinkedList is O(n) each; avoid
        // repeated searches by linking directly in the already-sorted sequence.
        Node** slot = &listData;
        while (i < left.size() || j < right.size()) {
            bool takeLeft = j == right.size() ||
                (i < left.size() && !(right[j] < left[i]));
            const Song& s = takeLeft ? left[i++] : right[j++];
            *slot = new Node(new Song(s));
            slot = &((*slot)->next);
            ++length;
        }
    }

    // O(n+m log m+n*m) worst case with naive sorted linked insertion.
    void mergeWithUnsorted(const std::vector<Song>& incoming) {
        auto snapshot = incoming;
        for (const Song& song : snapshot) addSong(song);
    }
};
#endif
