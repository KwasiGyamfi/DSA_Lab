#ifndef SONG_H
#define SONG_H

#include "ItemType.h"
#include <string>

class Song : public ItemType
{
public:
    std::string title;
    std::string artist;
    int duration;
    std::string filePath;

    Song(const std::string& t,
         const std::string& a,
         int d,
         const std::string& path);

    bool operator<(const Song& other) const;

    bool CompareTo(const ItemType& other) const override;
    bool LessThan(const ItemType& other) const override;
    void Print(std::ostream& out) const override;
};

#endif