
#include "Playlist.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

Playlist::Playlist()
    : currentIndex(0)
{
}

// O(1): Insert at the front of the linked list.
void Playlist::addSong(const Song& song)
{
    bool hadSongs = !IsEmpty();

    Insert(new Song(song));

    // Preserve the previously selected song.
    if (hadSongs)
        currentIndex++;
    else
        currentIndex = 0;
}

// O(n): Find and remove the first song with this title.
void Playlist::removeSong(const string& title)
{
    Node* current = listData;
    Node* previous = nullptr;
    int index = 0;

    while (current != nullptr)
    {
        Song* song = dynamic_cast<Song*>(current->item);

        if (song != nullptr && song->title == title)
        {
            if (previous == nullptr)
                listData = current->next;
            else
                previous->next = current->next;

            delete current;
            length--;

            if (length == 0)
                currentIndex = 0;
            else if (index < currentIndex)
                currentIndex--;
            else if (currentIndex >= length)
                currentIndex = length - 1;

            return;
        }

        previous = current;
        current = current->next;
        index++;
    }
}

// O(n): Locate the currently selected song.
Song* Playlist::getCurrentSong()
{
    if (IsEmpty())
        return nullptr;

    Node* current = listData;

    for (int i = 0; i < currentIndex && current != nullptr; i++)
        current = current->next;

    if (current == nullptr)
        return nullptr;

    return dynamic_cast<Song*>(current->item);
}

// O(1): Advance the selected index.
void Playlist::nextSong()
{
    if (!IsEmpty())
        currentIndex = (currentIndex + 1) % length;
}

// O(1): Move the selected index backward, wrapping around.
void Playlist::previousSong()
{
    if (!IsEmpty())
        currentIndex = (currentIndex + length - 1) % length;
}

// O(1): Validate and update the selected index.
bool Playlist::selectSong(int index)
{
    if (index < 0 || index >= length)
        return false;

    currentIndex = index;
    return true;
}

// O(n): Collect the playlist contents in order.
vector<Song> Playlist::getSongs() const
{
    vector<Song> songs;
    Node* current = listData;

    while (current != nullptr)
    {
        Song* song = dynamic_cast<Song*>(current->item);

        if (song != nullptr)
            songs.push_back(*song);

        current = current->next;
    }

    return songs;
}

// O(n log n): Sort using a temporary vector and rebuild the list.
void Playlist::sortByTitle()
{
    if (length < 2)
        return;

    Song* selected = getCurrentSong();
    string selectedPath = selected != nullptr ? selected->filePath : "";

    vector<Song> songs = getSongs();

    sort(songs.begin(), songs.end());

    Clear();
    currentIndex = 0;

    // Insert reverses order, so rebuild backward.
    for (auto it = songs.rbegin(); it != songs.rend(); ++it)
        addSong(*it);

    // Restore selection of the previously playing song.
    for (int i = 0; i < length; i++)
    {
        selectSong(i);
        Song* current = getCurrentSong();

        if (current != nullptr && current->filePath == selectedPath)
            return;
    }

    currentIndex = 0;
}


void Playlist::mergeFrom(const Playlist& other)
{
    // Snapshot the other playlist, including for self-merging.
    vector<Song> incoming = other.getSongs();

    if (incoming.empty())
        return;

    // Find the final node of this playlist.
    Node* last = listData;

    if (last != nullptr)
    {
        while (last->next != nullptr)
            last = last->next;
    }

    // Append new nodes without disturbing existing songs.
    for (const Song& song : incoming)
    {
        Node* newNode = new Node(new Song(song));

        if (listData == nullptr)
            listData = newNode;
        else
            last->next = newNode;

        last = newNode;
        length++;
    }
}

Song* Playlist::searchSong(const string& title)
{
    Node* current = listData;

    while (current != nullptr)
    {
        Song* song = dynamic_cast<Song*>(current->item);

        if (song != nullptr && song->title == title)
            return song;

        current = current->next;
    }

    return nullptr;
}

bool Playlist::exportToJson(const string& filename) const
{
    ofstream out(filename);

    if (!out.is_open())
        return false;

    // Quote and escape JSON string characters.
    auto escapeJson = [](const string& input)
    {
        string result;

        for (unsigned char c : input)
        {
            switch (c)
            {
                case '"':  result += "\\\""; break;
                case '\\': result += "\\\\"; break;
                case '\n': result += "\\n";  break;
                case '\r': result += "\\r";  break;
                case '\t': result += "\\t";  break;
                default:
                    if (c < 0x20)
                    {
                        const char* hex = "0123456789abcdef";
                        result += "\\u00";
                        result += hex[c >> 4];
                        result += hex[c & 0x0f];
                    }
                    else
                    {
                        result += static_cast<char>(c);
                    }
            }
        }

        return result;
    };

    vector<Song> songs = getSongs();

    out << "{\n";
    out << "  \"songs\": [\n";

    for (size_t i = 0; i < songs.size(); i++)
    {
        const Song& song = songs[i];

        out << "    {\n";
        out << "      \"title\": \"" << escapeJson(song.title) << "\",\n";
        out << "      \"artist\": \"" << escapeJson(song.artist) << "\",\n";
        out << "      \"duration\": " << song.duration << ",\n";
        out << "      \"filePath\": \"" << escapeJson(song.filePath) << "\"\n";
        out << "    }";

        if (i + 1 < songs.size())
            out << ",";

        out << "\n";
    }

    out << "  ]\n";
    out << "}\n";

    out.close();
    return out.good();
}