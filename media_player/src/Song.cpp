#include "Song.h"

using namespace std;

Song::Song(const string& t,
           const string& a,
           int d,
           const string& path)
    : title(t), artist(a), duration(d), filePath(path)
{
}

bool Song::operator<(const Song& other) const
{
    return title < other.title;
}

bool Song::CompareTo(const ItemType& other) const
{
    const Song* song = dynamic_cast<const Song*>(&other);

    return song != nullptr &&
           title == song->title &&
           artist == song->artist;
}

bool Song::LessThan(const ItemType& other) const
{
    const Song* song = dynamic_cast<const Song*>(&other);

    return song != nullptr && title < song->title;
}

void Song::Print(ostream& out) const
{
    out << title << " - " << artist
        << " (" << duration << " seconds)";
}