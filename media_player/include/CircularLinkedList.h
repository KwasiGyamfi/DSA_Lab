
#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "Song.h"
#include <iostream>

class CircularLinkedList
{
private:
    struct CircularNode
    {
        Song song;
        CircularNode* next;

        explicit CircularNode(const Song& s)
            : song(s), next(nullptr) {}
    };

    CircularNode* tail;
    int length;

public:
    CircularLinkedList()
        : tail(nullptr), length(0) {}

    ~CircularLinkedList()
    {
        Clear();
    }

    CircularLinkedList(const CircularLinkedList&) = delete;
    CircularLinkedList& operator=(const CircularLinkedList&) = delete;

    // O(1): Insert at the end using the tail pointer.
    void Insert(const Song& song)
    {
        CircularNode* node = new CircularNode(song);

        if (tail == nullptr)
        {
            tail = node;
            node->next = node;
        }
        else
        {
            node->next = tail->next;
            tail->next = node;
            tail = node;
        }

        length++;
    }

    // O(n): Search for and remove a song by title.
    bool Remove(const std::string& title)
    {
        if (tail == nullptr)
            return false;

        CircularNode* previous = tail;
        CircularNode* current = tail->next;

        for (int i = 0; i < length; i++)
        {
            if (current->song.title == title)
            {
                if (length == 1)
                {
                    delete current;
                    tail = nullptr;
                }
                else
                {
                    previous->next = current->next;

                    if (current == tail)
                        tail = previous;

                    delete current;
                }

                length--;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    // O(n): Search the circular list.
    bool IsPresent(const std::string& title) const
    {
        if (tail == nullptr)
            return false;

        CircularNode* current = tail->next;

        for (int i = 0; i < length; i++)
        {
            if (current->song.title == title)
                return true;

            current = current->next;
        }

        return false;
    }

    // O(1): Return the number of songs.
    int Length() const
    {
        return length;
    }

    // O(n): Display each song exactly once.
    void ListItems() const
    {
        if (tail == nullptr)
        {
            std::cout << "List is empty.\n";
            return;
        }

        CircularNode* current = tail->next;

        for (int i = 0; i < length; i++)
        {
            current->song.Print(std::cout);
            std::cout << '\n';
            current = current->next;
        }
    }

    // O(n): Release all nodes.
    void Clear()
    {
        if (tail == nullptr)
            return;

        CircularNode* current = tail->next;
        tail->next = nullptr;

        while (current != nullptr)
        {
            CircularNode* next = current->next;
            delete current;
            current = next;
        }

        tail = nullptr;
        length = 0;
    }
};

#endif
