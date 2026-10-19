#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <iostream>

class ItemType
{
public:
    virtual ~ItemType() = default;

    virtual bool CompareTo(const ItemType& other) const = 0;
    virtual bool LessThan(const ItemType& other) const = 0;
    virtual void Print(std::ostream& out) const = 0;
};

#endif